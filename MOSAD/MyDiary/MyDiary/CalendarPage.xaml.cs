using SQLitePCL;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace MyDiary
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class CalendarPage : Page
    {
        public CalendarPage() {
            this.InitializeComponent();
        }

        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
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

        private void PressDate(CalendarView sender, CalendarViewSelectedDatesChangedEventArgs args)
        {
            App.selectTimeFlag = false;
            if (DateTime.Compare(new DateTime(args.AddedDates[0].Year, args.AddedDates[0].Month, args.AddedDates[0].Day), new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day)) > 0)
            {
                return;
            }
            App.selectTime = new DateTime(args.AddedDates[0].Year, args.AddedDates[0].Month, args.AddedDates[0].Day);
            string date = "%" + args.AddedDates[0].Year.ToString() + '/' + args.AddedDates[0].Month.ToString() + '/' + args.AddedDates[0].Day.ToString() + "%";
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
    }
}
