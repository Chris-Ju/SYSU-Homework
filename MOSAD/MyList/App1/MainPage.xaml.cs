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
using SQLitePCL;
using MyList;

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
        string filePath = "ms-appx:///Assets/Background.jpg";
        public MainPage()
        {
            this.InitializeComponent();
            this.View_Model = ViewModels.TodoViewModels.GetInstance(Icon);
            ImageBrush imageBrush = new ImageBrush();
            imageBrush.ImageSource = new BitmapImage(new Uri("ms-appx:///Assets/timg.jpg", UriKind.Absolute));
            All.Background = imageBrush;

        }

        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            if (Grid_2.Visibility == Visibility.Collapsed)
            {
                Frame.Navigate(typeof(NewPage));
            }
            else
            {
                return;
            }
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            this.View_Model = ViewModels.TodoViewModels.GetInstance(Icon);
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
                    View_Model.AddTodoItem(Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, filePath, false);
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
                    using (var cust_stmt = App.conn.Prepare("INSERT INTO Customer (Title, Details, Date, ImageUrl, IsCompleted) VALUES (?, ?, ?, ?, ?)"))
                    {
                        cust_stmt.Bind(1, Title.Text);
                        cust_stmt.Bind(2, Detail.Text);
                        cust_stmt.Bind(3, Date.Date.ToString());
                        cust_stmt.Bind(4, filePath);
                        cust_stmt.Bind(5, "False");
                        cust_stmt.Step();
                    }
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
                    
                    using (var cust_stmt = App.conn.Prepare("UPDATE Customer SET Title = ?, Details = ?, Date = ?, ImageUrl = ? WHERE Id = ?"))
                    {
                        cust_stmt.Bind(1, Title.Text);
                        cust_stmt.Bind(2, Detail.Text);
                        cust_stmt.Bind(3, Date.Date.ToString());
                        cust_stmt.Bind(4, filePath);
                        cust_stmt.Bind(5, GetId());
                        cust_stmt.Step();
                    }
                    View_Model.UpdateTodoItem(View_Model.SelectItem.id, Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, filePath);
                    Date.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
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

            if (file != null)
            {
                IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read);
                BitmapImage bmp = new BitmapImage();
                bmp.SetSource(stream);
                this.Icon.Source = bmp;
                this.filePath = file.Path;

                // store to LocalFolder
                await ImageStorage.StorageImageFolder(stream, new Uri(file.Path));
            }
        }
        private void CancelBarClick(object sender, RoutedEventArgs e)
        {
            this.clear();
        }

        private void ListView_ItemClick(object sender, ItemClickEventArgs e)
        {
            View_Model.SelectItem = (Models.TodoItem)e.ClickedItem ;
            if (Grid_2.Visibility == Visibility.Collapsed)
            {
                Frame.Navigate(typeof(NewPage));
            }
            else
            {
                CreateBar.Content = "Update";
                Title.Text = View_Model.SelectItem.title;
                Detail.Text = View_Model.SelectItem.description;
                Date.Date = View_Model.SelectItem.date;
                Icon.Source = View_Model.SelectItem.source;
                filePath = View_Model.SelectItem.picPath;
                DeleteAppBarButton.Visibility = Visibility.Visible;
            }
        }

        private void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            
            using (var statement = App.conn.Prepare("DELETE FROM Customer WHERE Id = ?"))
            {
                statement.Bind(1, GetId());
                statement.Step();
            }
            View_Model.RemoveTodoItem(View_Model.SelectItem.id);
            CreateBar.Content = "Create";
            DeleteAppBarButton.Visibility = Visibility.Collapsed;
            this.clear();
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            bool susppending = ((App)App.Current).issuspend;
            DataTransferManager.GetForCurrentView().DataRequested -= OnShareDataRequested;
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
            Icon.Source = new BitmapImage(new Uri(Icon.BaseUri, "Assets/Background.jpg"));
            Date.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
        }

        private async void MenuFlyoutItem_Click(object sender, RoutedEventArgs e)
        {
            if (View_Model.SelectItem != null)
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
            request.Data.Properties.Title = View_Model.SelectItem.title;
            request.Data.SetText(View_Model.SelectItem.description);
            try
            {
                 StorageFile imageFile = await StorageFile.GetFileFromApplicationUriAsync(new Uri(View_Model.SelectItem.picPath));
                 request.Data.SetBitmap(RandomAccessStreamReference.CreateFromFile(imageFile));               
            }
            finally
            {
                getFile.Complete();
            }
            getFile.Complete();
            
        }

        private void search_Click(object sender, RoutedEventArgs e)
        {
            string q = "%" + searchText.Text + "%";
            using (var statement = App.conn.Prepare("SELECT * FROM Customer WHERE Title LIKE ? or Details LIKE ? or Date LIKE ?"))
            {
                statement.Bind(1, q);
                statement.Bind(2, q);
                statement.Bind(3, q);
                string os = "";
                while (statement.Step() != SQLiteResult.DONE)
                {
                    string tid = statement[0].ToString();
                    string ttitle = statement[1].ToString();
                    string tdetails = statement[2].ToString();
                    string tdate = statement[3].ToString();
                    // string dpicpath = statement[4].ToString();
                    os += "Title: " + ttitle + "; Details: " + tdetails + "; Date: " + tdate + "\n";
                }
                var i = new MessageDialog(os).ShowAsync();
            }
        }

        private int GetId()
        {
            string query = "%%";
            int id = 0; 
            string vtitle = View_Model.SelectItem.title;
            string vdetails = View_Model.SelectItem.description;
            using (var statement = App.conn.Prepare("SELECT * FROM Customer WHERE Id LIKE ? OR Title LIKE ? OR Details LIKE ? OR Date LIKE ?"))
            {
                statement.Bind(1, query);
                statement.Bind(2, query);
                statement.Bind(3, query);
                statement.Bind(4, query);

                while (statement.Step() != SQLiteResult.DONE)
                {
                    string did = statement[0].ToString();
                    string dtitle = statement[1].ToString();
                    string ddetails = statement[2].ToString();
                    if (vtitle == dtitle && vdetails == ddetails)
                    {
                        id = int.Parse(did);
                        break;
                    }
                }
            }
            return id;
        }

        private void checkBox_Click(object sender, RoutedEventArgs e)
        {
            for (int count = 0; count < View_Model.AllItems.Count; count++)
            {
                View_Model.SelectItem = View_Model.AllItems[count];
                Debug.WriteLine(View_Model.SelectItem.completed.ToString());
                using (var statement = App.conn.Prepare("UPDATE Customer SET IsCompleted = ? WHERE Id = ?"))
                {
                    statement.Bind(1, View_Model.SelectItem.completed.ToString());
                    statement.Bind(2, GetId());
                    statement.Step();
                }
                
            }
            View_Model.SelectItem = null;
        }
    }
}

