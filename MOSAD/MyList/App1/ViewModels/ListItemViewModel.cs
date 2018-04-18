using MyList;
using SQLitePCL;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MyList.Models;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI.Popups;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace MyList.ViewModels
{
    class TodoViewModels
    {
        private ObservableCollection<TodoItem> allItems = new ObservableCollection<TodoItem>();
        public ObservableCollection<TodoItem> AllItems { get { return this.allItems; } }

        private TodoItem selectItem = default(TodoItem);
        public TodoItem SelectItem { get { return selectItem; } set { this.selectItem = value; } }
        private static TodoViewModels Instance;
        public static TodoViewModels GetInstance(object e)
        {
            if (Instance == null)
            {
                Instance = new TodoViewModels(e);
            }
            return Instance;
        }

        private TodoViewModels(object e)
        {
            Image image = e as Image;
            string q = "%%";
            using (var statement = App.conn.Prepare("select * from Customer where Id like ? or Title like ? or Details like ? or Date like ?"))
            {
                statement.Bind(1, q);
                statement.Bind(2, q);
                statement.Bind(3, q);
                statement.Bind(4, q);

                while (statement.Step() != SQLiteResult.DONE)
                {
                    string tid = statement[0].ToString();
                    string ttitle = statement[1].ToString();
                    string tdetails = statement[2].ToString();
                    string ddate = statement[3].ToString();
                    string dpicpath = statement[4].ToString();
                    string dcomp = statement[5].ToString();
                    DateTime ddateconvert = Convert.ToDateTime(ddate);

                    BitmapImage timg = new BitmapImage();
                    
                    if(dpicpath == "ms-appx:///Assets/Background.jpg")
                    {
                        timg = new BitmapImage(new Uri(dpicpath));
                    }
                    else
                    {
                        getImg(dpicpath, timg);
                    }
                    bool ddcomp = (dcomp == "True") ? true : false;

                    this.allItems.Add(new TodoItem(ttitle, tdetails, ddateconvert, timg, dpicpath, ddcomp));
                }
            }
        }

        private async void getImg(string path, BitmapImage img)
        {
            await ImageStorage.GetLoacalFolderImage(new Uri(path), img);
        }


        public void AddTodoItem(string title, string description, DateTime d, ImageSource s, string picPath, bool comp)
        {
            this.allItems.Add(new TodoItem(title, description, d, s, picPath, comp));
        }

        public void RemoveTodoItem(string id)
        {
            this.allItems.Remove(selectItem);
            this.selectItem = null;
        }

        public void UpdateTodoItem(string id, string title, string description, DateTime d, ImageSource s, string picPath)
        {
            this.selectItem.id = id;
            this.selectItem.title = title;
            this.selectItem.description = description;
            this.selectItem.date = d;
            this.selectItem.source = s;
            this.selectItem.picPath = picPath;
            this.selectItem = null;
        }


    }
}
