using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lib;

namespace DesktopApp.Event
{
    public class EntityCreateEvent : IEvent
    {
        public string Name
        {
            get
            {
                return this.GetType().Name;
            }
        }

        public EntityCreateEvent(IEntity entity)
        {
            this.Entity = entity;
        }

        public IEntity Entity;
    }
}
