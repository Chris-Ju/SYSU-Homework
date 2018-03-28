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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace App1
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {

        public MainPage()
        {
            this.InitializeComponent();
            this.ViewModels_1 = new ViewModels.TodoViewModels();
            ImageBrush imageBrush = new ImageBrush();
            imageBrush.ImageSource = new BitmapImage(new Uri("ms-appx:///Assets/timg.jpg", UriKind.Absolute));
            All.Background = imageBrush;
        }
        ViewModels.TodoViewModels ViewModels_1 { get; set; }
        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            if (Grid_2.Visibility == Visibility.Collapsed)
            {
                Frame.Navigate(typeof(App1.BlankPage1), ViewModels_1);
            }
            else
            {
                return;
            }
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            Windows.UI.Core.SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
            Windows.UI.Core.AppViewBackButtonVisibility.Collapsed;
            if (e.Parameter.GetType() == typeof(ViewModels.TodoViewModels))
            {
                this.ViewModels_1 = (ViewModels.TodoViewModels)(e.Parameter);
            }
        }

        private async void button1_Click(object sender, RoutedEventArgs e)
        {
            if (button1.Content.ToString() == "Create")
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
                if (DateTime.Compare(new DateTime(DatePicker_1.Date.Year, DatePicker_1.Date.Month, DatePicker_1.Date.Day), new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day)) < 0)
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
                    ViewModels_1.AddTodoItem(Title.Text, Detail.Text, new DateTime(DatePicker_1.Date.Year, DatePicker_1.Date.Month, DatePicker_1.Date.Day), this.Image_1.Source);
                    DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                    await messageDialog.ShowAsync();
                    button1.Content = "Create";
                    Title.Text = "";
                    Detail.Text = "";
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
                if (DateTime.Compare(new DateTime(DatePicker_1.Date.Year, DatePicker_1.Date.Month, DatePicker_1.Date.Day), new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day)) < 0)
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
                    ViewModels_1.UpdateTodoItem(ViewModels_1.SelectedItem.id, Title.Text, Detail.Text, new DateTime(DatePicker_1.Date.Year, DatePicker_1.Date.Month, DatePicker_1.Date.Day), this.Image_1.Source);
                    var messageDialog = new MessageDialog("Update successfully!");
                    DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                    await messageDialog.ShowAsync();
                    this.Frame.Navigate(typeof(MainPage), ViewModels_1);
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

            StorageFile file = await openPicker.PickSingleFileAsync();
            BitmapImage srcImage = new BitmapImage();

            if (file != null)
            {
                using (IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read))
                {
                    await srcImage.SetSourceAsync(stream);
                    this.Image_1.Source = srcImage;
                }
            }
        }
        private void button2_Click(object sender, RoutedEventArgs e)
        {
            Title.Text = "";
            Detail.Text = "";
            DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
        }

        private void ListView_ItemClick(object sender, ItemClickEventArgs e)
        {
            ViewModels_1.SelectedItem = e.ClickedItem as Models.TodoItem;
            if (Grid_2.Visibility == Visibility.Collapsed)
            {
                Frame.Navigate(typeof(App1.BlankPage1), ViewModels_1);
            }
            else
            {
                button1.Content = "Update";
                Title.Text = ViewModels_1.SelectedItem.title;
                Detail.Text = ViewModels_1.SelectedItem.description;
                DatePicker_1.Date = ViewModels_1.SelectedItem.date;
                DeleteAppBarButton.Visibility = Visibility.Visible;
            }
        }

        private async void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            ViewModels_1.RemoveTodoItem(ViewModels_1.SelectedItem.id);
            var messageDialog = new MessageDialog("Delete successfully!");
            await messageDialog.ShowAsync();
            button1.Content = "Create";
            DeleteAppBarButton.Visibility = Visibility.Collapsed;
            Title.Text = "";
            Detail.Text = "";
            DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
        }
    }
}
