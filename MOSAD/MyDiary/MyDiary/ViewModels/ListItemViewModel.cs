using MyDiary.Models;
using SQLitePCL;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI.Popups;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace MyDiary.ViewModels
{

    public class ListItemViewModel
    {
        private ObservableCollection<ListItem> allItems = new ObservableCollection<ListItem>();
        public ObservableCollection<ListItem> AllItems { get { return this.allItems; } }

        public ListItemViewModel()
        {
            
        }
        public void AddListItem(string title, string description, string tag, DateTime d)
        {
            this.allItems.Add(new ListItem(title, description, tag, d));
        }
     
    }
}
