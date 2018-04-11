using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace MyList
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>

    public sealed partial class NewPage : Page
    {

        StorageFile file;

        public NewPage()
        {
            this.InitializeComponent();
            ImageBrush imageBrush = new ImageBrush();
            imageBrush.ImageSource = new BitmapImage(new Uri("ms-appx:///Assets/timg.jpg", UriKind.Absolute));
            All.Background = imageBrush;
        }
        private ViewModels.TodoViewModels ViewModel;
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            this.ViewModel = ViewModels.TodoViewModels.GetInstance();
            
            if (e.NavigationMode == NavigationMode.New)
            {
                ApplicationData.Current.LocalSettings.Values.Remove("NewPage");
                if (ViewModel.SelectedItem == null)
                {
                    return;
                }
                else
                {
                    CreateBar.Content = "Update";
                    DeleteAppBarButton.Visibility = Visibility.Visible;
                    Title.Text = ViewModel.SelectedItem.title;
                    Detail.Text = ViewModel.SelectedItem.description;
                    Date.Date = ViewModel.SelectedItem.date;
                    Icon.Source = ViewModel.SelectedItem.source;
                }
            }
            else
            {
                if (ApplicationData.Current.LocalSettings.Values.ContainsKey("NewPage"))
                {
                    var composite = ApplicationData.Current.LocalSettings.Values["NewPage"] as ApplicationDataCompositeValue;
                    Title.Text = (string)composite["title"];
                    Detail.Text = (string)composite["detail"];
                    Date.Date = (DateTimeOffset)composite["date"];
                    ///Icon.Source = (ImageSource)composite["image"];
                    ///View_Model = (ViewModels.TodoViewModels)composite["viewModel"];
                    ApplicationData.Current.LocalSettings.Values.Remove("NewPage");
                    SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility = AppViewBackButtonVisibility.Visible;
                }
            }
        }
        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            bool susppending = ((App)App.Current).issuspend;

            if (susppending)
            {
                ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
                composite["title"] = Title.Text;
                composite["detail"] = Detail.Text;
                ///composite["imgae"] = Icon.Source;
                composite["date"] = Date.Date;
                ///composite["viewModel"] = View_Model;
                ApplicationData.Current.LocalSettings.Values["NewPage"] = composite;
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
                    ViewModel.AddTodoItem(Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, file);                    
                    await messageDialog.ShowAsync();
                    Frame rootFrame = Window.Current.Content as Frame;
                    rootFrame.GoBack();

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
                    ViewModel.UpdateTodoItem(ViewModel.SelectedItem.GetId(), Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, file);
                    var messageDialog = new MessageDialog("Update successfully!");
                    await messageDialog.ShowAsync();
                    Frame rootFrame = Window.Current.Content as Frame;
                    rootFrame.GoBack();
                }
            }
        }

        private void CancelBarClick(object sender, RoutedEventArgs e)
        {
            this.clear();
        }

        private async void AppBarButton_ClickAsync(object sender, RoutedEventArgs e)
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
                //using (IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read))
                //{
                //    await srcImage.SetSourceAsync(stream);
                //    this.Icon.Source = srcImage;
                // }
                IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read);
                // var i = new MessageDialog(file.Name).ShowAsync();
                BitmapImage bitmapImage = new BitmapImage();
                await bitmapImage.SetSourceAsync(stream);
                Icon.Source = bitmapImage;
            }

        }
        private async void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.RemoveTodoItem(ViewModel.SelectedItem.GetId());
            var messageDialog = new MessageDialog("Delete successfully!");
            await messageDialog.ShowAsync();
            Frame rootFrame = Window.Current.Content as Frame;
            rootFrame.GoBack();
        }

        private void clear()
        {
            Title.Text = "";
            Detail.Text = "";
            Date.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
        }
    }
}
