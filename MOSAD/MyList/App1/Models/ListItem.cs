using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Media;

namespace MyList.Models
{
    class TodoItem
    {
        public TodoItem(String title, String description, DateTime date, ImageSource source)
        {
            this.id = Guid.NewGuid().ToString();
            this.title = title;
            this.description = description;
            this.date = date;
            this.source = source;
            this.completed = false;
        }
        public String id;

        public String title { get; set; }

        public String description { get; set; }

        public Boolean completed { get; set; }

        public DateTime date { get; set; }

        public ImageSource source { get; set; }
    }
}
