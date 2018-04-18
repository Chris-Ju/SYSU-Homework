using SQLitePCL;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using MyList;
using MyList.ViewModels;
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
        private string filePath = "ms-appx:///Assets/Background.jpg";
        public NewPage()
        {
            this.InitializeComponent();
            ImageBrush imageBrush = new ImageBrush();
            imageBrush.ImageSource = new BitmapImage(new Uri("ms-appx:///Assets/timg.jpg", UriKind.Absolute));
            All.Background = imageBrush;
        }
        private TodoViewModels ViewModel;
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            ViewModel = TodoViewModels.GetInstance(Icon);
            if (e.NavigationMode == NavigationMode.New)
            {
                ApplicationData.Current.LocalSettings.Values.Remove("NewPage");
                if (ViewModel.SelectItem == null)
                {
                    return;
                }
                else
                {
                    CreateBar.Content = "Update";
                    DeleteAppBarButton.Visibility = Visibility.Visible;
                    Title.Text = ViewModel.SelectItem.title;
                    Detail.Text = ViewModel.SelectItem.description;
                    Date.Date = ViewModel.SelectItem.date;
                    Icon.Source = ViewModel.SelectItem.source;
                    this.filePath = ViewModel.SelectItem.picPath;
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
                    ViewModel.AddTodoItem(Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, filePath, false);
                    using (var cust_stmt = App.conn.Prepare("insert into Customer (Title, Details, Date, ImageUrl, IsCompleted) values (?, ?, ?, ?, ?)"))
                    {
                        cust_stmt.Bind(1, Title.Text);
                        cust_stmt.Bind(2, Detail.Text);
                        cust_stmt.Bind(3, Date.Date.ToString());
                        cust_stmt.Bind(4, filePath);
                        cust_stmt.Bind(5, "False");
                        cust_stmt.Step();
                    }
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
                    using (var cust_stmt = App.conn.Prepare("UPDATE Customer SET Title = ?, Details = ?, Date = ?, ImageUrl = ? WHERE Id = ?"))
                    {
                        cust_stmt.Bind(1, Title.Text);
                        cust_stmt.Bind(2, Detail.Text);
                        cust_stmt.Bind(3, Date.Date.ToString());
                        cust_stmt.Bind(4, filePath);
                        cust_stmt.Bind(5, GetId());
                        cust_stmt.Step();
                    }
                    ViewModel.UpdateTodoItem(ViewModel.SelectItem.id, Title.Text, Detail.Text, new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), this.Icon.Source, filePath);
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
                IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read);
                BitmapImage bmp = new BitmapImage();
                bmp.SetSource(stream);
                this.Icon.Source = bmp;
                this.filePath = file.Path;

                // store to LocalFolder
                await ImageStorage.StorageImageFolder(stream, new Uri(file.Path));
            }

        }
        private void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
           
            using (var statement = App.conn.Prepare("DELETE FROM Customer WHERE Id = ?"))
            {
                statement.Bind(1, GetId());
                statement.Step();
            }
            ViewModel.RemoveTodoItem(ViewModel.SelectItem.id);
            Frame rootFrame = Window.Current.Content as Frame;
            rootFrame.GoBack();
        }

        private void clear()
        {
            Title.Text = "";
            Detail.Text = "";
            Date.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
        }

        private int GetId()
        {
            string query = "%%";
            int id = 0;
            string vtitle = ViewModel.SelectItem.title;
            string vdetails = ViewModel.SelectItem.description;
            using (var statement = App.conn.Prepare("select * from Customer where Id like ? or Title like ? or Details like ? or Date like ?"))
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
                    if (vtitle == dtitle &&
                        vdetails == ddetails)
                    {
                        id = int.Parse(did);
                        break;
                    }
                }
            }
            return id;
        }
    }
}
