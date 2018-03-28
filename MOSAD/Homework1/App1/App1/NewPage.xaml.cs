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

namespace App1
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>

    public sealed partial class BlankPage1 : Page
    {

        public BlankPage1()
        {
            this.InitializeComponent();
            ImageBrush imageBrush = new ImageBrush();
            imageBrush.ImageSource = new BitmapImage(new Uri("ms-appx:///Assets/timg.jpg", UriKind.Absolute));
            All.Background = imageBrush;
        }
        private ViewModels.TodoViewModels ViewModels_1;
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            ViewModels_1 = ((ViewModels.TodoViewModels)e.Parameter);
            if (ViewModels_1.SelectedItem == null)
            {
                return;
            }
            else
            {
                button1.Content = "Update";
                DeleteAppBarButton.Visibility = Visibility.Visible;
                Title.Text = ViewModels_1.SelectedItem.title;
                Detail.Text = ViewModels_1.SelectedItem.description;
                DatePicker_1.Date = ViewModels_1.SelectedItem.date;
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
                    await messageDialog.ShowAsync();
                    DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                    button1.Content = "Create";
                    Title.Text = "";
                    Detail.Text = "";
                    this.Frame.Navigate(typeof(MainPage), ViewModels_1);

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
                    await messageDialog.ShowAsync();
                    DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                    button1.Content = "Create";
                    Title.Text = "";
                    Detail.Text = "";
                    this.Frame.Navigate(typeof(MainPage), ViewModels_1);
                }
            }
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            Title.Text = "";
            Detail.Text = "";
            DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
        }

        private async void AppBarButton_ClickAsync(object sender, RoutedEventArgs e)
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
        private async void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            ViewModels_1.RemoveTodoItem(ViewModels_1.SelectedItem.id);
            var messageDialog = new MessageDialog("Delete successfully!");
            await messageDialog.ShowAsync();
            button1.Content = "Create";
            Title.Text = "";
            Detail.Text = "";
            DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
            this.Frame.Navigate(typeof(MainPage), ViewModels_1);
        }
    }
}
