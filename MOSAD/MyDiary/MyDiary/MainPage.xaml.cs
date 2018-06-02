using Newtonsoft.Json;
using System;
using System.IO;
using Windows.Storage;
using Windows.Storage.AccessCache;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Notifications;
using Windows.Data.Xml.Dom;
using Windows.ApplicationModel.DataTransfer;
using SQLitePCL;
using System.Text;
using System.Net.Http;
using System.Collections.ObjectModel;
using System.Diagnostics;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace MyDiary
{

    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        ObservableCollection<String> tags = new ObservableCollection<String>();
        private ViewModels.ListItemViewModel ViewModel;
        private Models.ListItem Item;
        public MainPage() {
            var db = App.conn;
            using (var statement = db.Prepare("SELECT * FROM Tags"))
            {
                while (SQLiteResult.DONE != statement.Step())
                {
                    tags.Add((string)statement[0]);
                }
            }
            tags.Add("全部");
            if (App.ViewModel != null)
            {
                ViewModel = App.ViewModel;
                App.ViewModel = null;
            }
            else
            {
                ViewModel = new ViewModels.ListItemViewModel();
                
                using (var statement = App.conn.Prepare("select * from Items"))
                {
                    while (statement.Step() != SQLiteResult.DONE)
                    {
                        string tid = statement[0].ToString();
                        string ttitle = statement[1].ToString();
                        string tdetails = statement[2].ToString();
                        string ddate = statement[3].ToString();
                        string ttag = statement[4].ToString();
                        DateTime ddateconvert = Convert.ToDateTime(ddate);

                        ViewModel.AddListItem(ttitle, tdetails, ttag, ddateconvert);
                    }
                }
            }
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e) {
            DataTransferManager dataTransferManager = DataTransferManager.GetForCurrentView();
            dataTransferManager.DataRequested += DataTransferManager_DataRequested;
            Windows.UI.Core.SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
            Windows.UI.Core.AppViewBackButtonVisibility.Collapsed;
            base.OnNavigatedTo(e);
            if (e.NavigationMode == NavigationMode.New) {
                ApplicationData.Current.LocalSettings.Values.Remove("mainpage");
            } else {

            }
        }
        /// <summary>
        /// 点击增加按钮触发的新建Item函数
        /// </summary>
        private void AddAppBarButton_Click(object sender, RoutedEventArgs e) {
            string date = "%" + DateTime.Now.Year.ToString() + '/' + DateTime.Now.Month.ToString() + '/' + DateTime.Now.Day.ToString() + "%";
            App.item = null;
            using (var statement = App.conn.Prepare("select * from Items WHERE Date LIKE ?"))
            {
                statement.Bind(1, date);
                while (statement.Step() != SQLiteResult.DONE)
                {
                    string tid = statement[0].ToString();
                    string ttitle = statement[1].ToString();
                    string tdetails = statement[2].ToString();
                    string ddate = statement[3].ToString();
                    string tag = statement[4].ToString();
                    DateTime ddateconvert = Convert.ToDateTime(ddate);
                    App.item = new Models.ListItem(ttitle, tdetails, tag, ddateconvert);
                }
            }
            Frame root = Window.Current.Content as Frame;
            root.Navigate(typeof(NewPage));
        }

        /// <summary>
        /// 点击Item触发的跳转函数
        /// </summary>
        private void ListItem_ItemClicked(object sender, ItemClickEventArgs e)
        {
            Item = (Models.ListItem)e.ClickedItem;
            App.item = Item;
            Frame root = Window.Current.Content as Frame;
            root.Navigate(typeof(NewPage));      
        }


        /// <summary>
        /// 点击设置按钮触发的函数
        /// </summary>
        private void Setting_Clicked(object sender, RoutedEventArgs e) {
            var data = (sender as FrameworkElement).DataContext;
            var item = ItemListView.ContainerFromItem(data) as ListViewItem;
            Item = item.Content as Models.ListItem;
        }


        private void Share(object sender, RoutedEventArgs e) {
            DataTransferManager.ShowShareUI();
        }

        /// <summary>
        /// 分享事件处理
        /// </summary>
        private void DataTransferManager_DataRequested(DataTransferManager sender, DataRequestedEventArgs args) {
            DataRequest request = args.Request;
            request.Data.SetText(Item.description);
            request.Data.Properties.Title = Item.title;
            request.Data.Properties.Description = Item.description;
        }

        /// <summary>
        /// 搜索
        /// </summary>
        private void Search(object sender, RoutedEventArgs e) {
            var db = App.conn;
            ViewModel = new ViewModels.ListItemViewModel();
            string content = searchBox.Text.Trim();
            if (content != "") {
                string searchSQL = @"SELECT * FROM Items WHERE Title LIKE '%" + content + "%' " +
                                                               "OR Details LIKE '%" + content + "%' " +
                                                               "OR Date LIKE '%" + content + "%'";
                using (var statement = db.Prepare(searchSQL)) {
                    while (SQLiteResult.DONE != statement.Step()) {
                        string tid = statement[0].ToString();
                        string ttitle = statement[1].ToString();
                        string tdetails = statement[2].ToString();
                        string ddate = statement[3].ToString();
                        string ttag = statement[4].ToString();
                        DateTime ddateconvert = Convert.ToDateTime(ddate);

                        ViewModel.AddListItem(ttitle, tdetails, ttag, ddateconvert);

                    }
                }
                Frame root = Window.Current.Content as Frame;
                App.ViewModel = ViewModel;
                root.Navigate(typeof(MainPage));
            }
        }

        private void Calendar_Click(object sender, RoutedEventArgs e)
        {
            Frame root = Window.Current.Content as Frame;
            root.Navigate(typeof(CalendarPage));
        }

        private void Tags_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var db = App.conn;
            ViewModel = new ViewModels.ListItemViewModel();
            if (Tags.SelectedValue.ToString() != "全部")
            {
                string searchSQL = @"SELECT * FROM Items WHERE Tag = '" + Tags.SelectedValue.ToString() + "'";
                using (var statement = db.Prepare(searchSQL))
                {
                    while (SQLiteResult.DONE != statement.Step())
                    {
                        string tid = statement[0].ToString();
                        string ttitle = statement[1].ToString();
                        string tdetails = statement[2].ToString();
                        string ddate = statement[3].ToString();
                        string ttag = statement[4].ToString();
                        DateTime ddateconvert = Convert.ToDateTime(ddate);

                        ViewModel.AddListItem(ttitle, tdetails, ttag, ddateconvert);

                    }
                }
            }
            else
            {
                using (var statement = App.conn.Prepare("select * from Items"))
                {
                    while (statement.Step() != SQLiteResult.DONE)
                    {
                        string tid = statement[0].ToString();
                        string ttitle = statement[1].ToString();
                        string tdetails = statement[2].ToString();
                        string ddate = statement[3].ToString();
                        string ttag = statement[4].ToString();
                        DateTime ddateconvert = Convert.ToDateTime(ddate);

                        ViewModel.AddListItem(ttitle, tdetails, ttag, ddateconvert);
                    }
                }
            }
            Frame root = Window.Current.Content as Frame;
            App.ViewModel = ViewModel;
            root.Navigate(typeof(MainPage));
        }

        private void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            if (Item != null)
            {
                var db = App.conn;
                string date = "%" + Item.date.Date.Year.ToString() + "/" + Item.date.Date.Month.ToString() + "/" + Item.date.Date.Day.ToString() + "%";
                string sql = @"DELETE FROM Items WHERE Date like ?";
                try
                {
                    using (var res = db.Prepare(sql))
                    {
                        res.Bind(1, date);
                        res.Step();
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                    throw;
                }
                Frame.Navigate(typeof(MainPage));
            }
            Item = null;
        }
    }
}
