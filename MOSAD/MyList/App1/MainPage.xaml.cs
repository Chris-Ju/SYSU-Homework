using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Windows;
using Windows.UI.Popups;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Core;
using Windows.UI.Xaml.Media.Imaging;
using System.Diagnostics;
using Windows.ApplicationModel.DataTransfer;
using Windows.UI.Notifications;
using Windows.Data.Xml.Dom;

/// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace MyList
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private ViewModels.TodoViewModels View_Model = null;
        StorageFile file;
        public MainPage()
        {
            this.InitializeComponent();
            this.View_Model = ViewModels.TodoViewModels.GetInstance();
            ImageBrush imageBrush = new ImageBrush();
            imageBrush.ImageSource = new BitmapImage(new Uri("ms-appx:///Assets/timg.jpg", UriKind.Absolute));
            All.Background = imageBrush;

        }

        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            if (Grid_2.Visibility == Visibility.Collapsed)
            {
                Frame.Navigate(typeof(MyList.NewPage));
            }
            else
            {
                return;
            }
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            this.View_Model = ViewModels.TodoViewModels.GetInstance();
            DataTransferManager.GetForCurrentView().DataRequested += OnShareDataRequested;
            var updator = TileUpdateManager.CreateTileUpdaterForApplication();
            updator.Clear();
            for (int count = 0; count < View_Model.AllItems.Count; count++)
            {
                XmlDocument tile = new XmlDocument();
                tile.LoadXml(File.ReadAllText("Tile.xml"));
                XmlNodeList tileText = tile.GetElementsByTagName("text");
                for (int i = 0; i < tileText.Count; i++)
                {
                    ((XmlElement)tileText[i]).InnerText = View_Model.AllItems[count].title;
                    i++;
                    ((XmlElement)tileText[i]).InnerText = View_Model.AllItems[count].description;

                }
                TileNotification notification = new TileNotification(tile);
                updator.Update(notification);
            }
            TileUpdateManager.CreateTileUpdaterForApplication().EnableNotificationQueue(true);
            if (e.NavigationMode == NavigationMode.New)
            {
                ApplicationData.Current.LocalSettings.Values.Remove("NewPage");
            }
            else
            {
                if (ApplicationData.Current.LocalSettings.Values.ContainsKey("NewPage"))
                {
                    var composite = ApplicationData.Current.LocalSettings.Values["NewPage"] as ApplicationDataCompositeValue;
                    Title.Text = (string)composite["title"];
                    Detail.Text = (string)composite["detail"];
                    Date.Date = (DateTimeOffset)composite["date"];
                    //Icon.Source = new BitmapImage(new Uri((string)composite["image"]));
                    ApplicationData.Current.LocalSettings.Values.Remove("NewPage");
                }
            }
        }

        private async void CreateBarClick(object sender, RoutedEventArgs e)
        {
            if (CreateBar.Content.ToString() == "Create")
            {
                String reason = "";
                Boolean flag = false;
                if (Title.Text == "")
                {
                    reason = "Title is empty!\n";
                }
                if (Detail.Text == "")
                {
                    reason += "Detail is empty!\n";
                }
                if (DateTime.Compare(new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day)) < 0)
                {
                    reason += "Date is wrong!\n";
                }
                if (reason == "")
                {
                    flag = true;
                }
                if (!flag)
                {
                    var messageDialog = new MessageDialog(reason);
                    await messageDialog.ShowAsync();
                }
                else
                {
                    var messageDialog = new MessageDialog("Create successfully!");  
                    
                    View_Model.AddTodoItem(Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, file);
                    Date.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                    XmlDocument tile = new XmlDocument();
                    tile.LoadXml(File.ReadAllText("Tile.xml"));
                    XmlNodeList tileText = tile.GetElementsByTagName("text");
                    for (int i = 0; i < tileText.Count; i++)
                    {
                        ((XmlElement)tileText[i]).InnerText = View_Model.AllItems[View_Model.AllItems.Count - 1].title;
                        i++;
                        ((XmlElement)tileText[i]).InnerText = View_Model.AllItems[View_Model.AllItems.Count - 1].description;

                    }
                    TileNotification notification = new TileNotification(tile);
                    var updator = TileUpdateManager.CreateTileUpdaterForApplication();
                    updator.Update(notification);
                    TileUpdateManager.CreateTileUpdaterForApplication().EnableNotificationQueue(true);
                    await messageDialog.ShowAsync();
                    this.clear();
                }
            }
            else
            {
                String reason = "";
                Boolean flag = false;
                if (Title.Text == "")
                {
                    reason = "Title is empty!\n";
                }
                if (Detail.Text == "")
                {
                    reason += "Detail is empty!\n";
                }
                if (DateTime.Compare(new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day)) < 0)
                {
                    reason += "Date is wrong!\n";
                }
                if (reason == "")
                {
                    flag = true;
                }
                if (!flag)
                {
                    var messageDialog = new MessageDialog(reason);
                    await messageDialog.ShowAsync();
                }
                else
                {
                    View_Model.UpdateTodoItem(View_Model.SelectedItem.GetId(), Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, file);
                    var messageDialog = new MessageDialog("Update successfully!");
                    Date.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                    await messageDialog.ShowAsync();
                    this.Frame.Navigate(typeof(MainPage));
                    Frame rootFrame = Window.Current.Content as Frame;
                    rootFrame.GoBack();
                }
            } 
        }
        private async void AppBarButton_1_ClickAsync(object sender, RoutedEventArgs e)
        {
            FileOpenPicker openPicker = new FileOpenPicker();
            openPicker.ViewMode = PickerViewMode.Thumbnail;
            openPicker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;

            openPicker.FileTypeFilter.Add(".jpg");
            openPicker.FileTypeFilter.Add(".jpeg");
            openPicker.FileTypeFilter.Add(".png");

            file = await openPicker.PickSingleFileAsync();
            BitmapImage srcImage = new BitmapImage();

            if (file != null)
            {
                IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read);
                // var i = new MessageDialog(file.Name).ShowAsync();
                BitmapImage bitmapImage = new BitmapImage();
                await bitmapImage.SetSourceAsync(stream);
                Icon.Source = bitmapImage;
            }
        }
        private void CancelBarClick(object sender, RoutedEventArgs e)
        {
            this.clear();
        }

        private void ListView_ItemClick(object sender, ItemClickEventArgs e)
        {
            View_Model.SelectedItem = e.ClickedItem as Models.TodoItem;
            if (Grid_2.Visibility == Visibility.Collapsed)
            {
                Frame.Navigate(typeof(NewPage));
            }
            else
            {
                CreateBar.Content = "Update";
                Title.Text = View_Model.SelectedItem.title;
                Detail.Text = View_Model.SelectedItem.description;
                Date.Date = View_Model.SelectedItem.date;
                Icon.Source = View_Model.SelectedItem.source;
                DeleteAppBarButton.Visibility = Visibility.Visible;
            }
        }

        private async void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            View_Model.RemoveTodoItem(View_Model.SelectedItem.GetId());
            var messageDialog = new MessageDialog("Delete successfully!");
            await messageDialog.ShowAsync();
            CreateBar.Content = "Create";
            DeleteAppBarButton.Visibility = Visibility.Collapsed;
            this.clear();
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            bool susppending = ((App)App.Current).issuspend;
            DataTransferManager.GetForCurrentView().DataRequested -= OnShareDataRequested;
            if (susppending)
            {
                ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
                composite["title"] = Title.Text;
                composite["detail"] = Detail.Text;
                //composite["imgae"] = (Icon.Source as BitmapImage).UriSource.OriginalString;
                composite["date"] = Date.Date;
                ApplicationData.Current.LocalSettings.Values["NewPage"] = composite;
            }
            
        }
        private void clear()
        {
            Title.Text = "";
            Detail.Text = "";
            Date.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
        }

        private async void MenuFlyoutItem_Click(object sender, RoutedEventArgs e)
        {
            if (View_Model.SelectedItem != null)
            {
                DataTransferManager.ShowShareUI();
            }
            else
            {
                var messageDialog = new MessageDialog("Please selected the item first.");
                await messageDialog.ShowAsync();
            }
        }

        private async void OnShareDataRequested(DataTransferManager sender, DataRequestedEventArgs args)
        {
            DataRequest request = args.Request;
            DataRequestDeferral getFile = args.Request.GetDeferral();
            request.Data.Properties.Title = View_Model.SelectedItem.title;
            request.Data.SetText(View_Model.SelectedItem.description);
            try
            {
                if (View_Model.SelectedItem.f != null)
                {
                    request.Data.Properties.Thumbnail = RandomAccessStreamReference.CreateFromFile(View_Model.SelectedItem.f);
                    request.Data.SetBitmap(RandomAccessStreamReference.CreateFromFile(View_Model.SelectedItem.f));
                }
                else
                {
                    StorageFile imageFile = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///Assets/Background.jpg"));
                    request.Data.SetBitmap(RandomAccessStreamReference.CreateFromFile(imageFile));
                }
            }
            finally
            {
                getFile.Complete();
            }
            getFile.Complete();
            
        }
    }
}

