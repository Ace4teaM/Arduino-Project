/*
   Extension de la classe d'entité DisplayContent

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications seront perdues
   
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Globalization;
using System.Reflection;
using System.Collections.ObjectModel;
using Lib;
using AppData.Format;
using System.IO;
using System.Runtime.Serialization;
using System.Xml;

namespace AppData.Entity
{
    /// <summary>
    /// Implémente la définition de l'entité
    /// </summary>
   [Serializable]

    public partial class DisplayContent : IEntity, ISerializable, IEntitySerializable    {
         #region Constructor
         public DisplayContent(){

            // Elements
            this.elements = new Collection<DisplayElement>();
            // w
            this.w = new Int32();
            // h
            this.h = new Int32();
            // x
            this.x = new Int32();
            // y
            this.y = new Int32();
         }
         
         public DisplayContent(int w, int h, int x, int y) : this(){
            this.w = w;
            this.h = h;
            this.x = x;
            this.y = y;
         }
         #endregion // Constructor
         
          public string EntityName { get{ return "DisplayContent"; } }

         #region State
        private EntityState entityState;
        public EntityState EntityState { get{ return entityState; } set{ entityState = value; } }

         #endregion // State
        
         #region Fields
         // Largeur
         protected int w;
         public int W { get{ return w; } set{ w = value; } }
         // Hauteur
         protected int h;
         public int H { get{ return h; } set{ h = value; } }
         // Position X
         protected int x;
         public int X { get{ return x; } set{ x = value; } }
         // Position Y
         protected int y;
         public int Y { get{ return y; } set{ y = value; } }
         #endregion // Fields

         #region Associations
         // 
         protected Project project;
         public virtual Project Project { get{ return project; } set{ project = value; } }
         // 
         protected Collection<DisplayElement> elements;
         public virtual Collection<DisplayElement> Elements { get{ return elements; } set{ elements = value; } }
         public void AddElements(DisplayElement obj){
            obj.Content = this;
            Elements.Add(obj);
         }
         
         public void RemoveElements(DisplayElement obj){
            obj.Content = null;
            Elements.Remove(obj);
         }
         #endregion // Associations

         #region Methods
         public override string ToString()
         {
             string result = this.GetType().Name+":"+Environment.NewLine+"-----------------------------"+Environment.NewLine;
             result += "w = " + w + Environment.NewLine;
             result += "h = " + h + Environment.NewLine;
             result += "x = " + x + Environment.NewLine;
             result += "y = " + y + Environment.NewLine;
             return result;
         }

         #endregion // Methods

       #region ISerializable
        // Implement this method to serialize data. The method is called on serialization.
        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            info.AddValue("w", w, typeof(int));
            info.AddValue("h", h, typeof(int));
            info.AddValue("x", x, typeof(int));
            info.AddValue("y", y, typeof(int));
                 }
       #endregion // ISerializable
       
       #region Serialization
       public void ReadBinary(BinaryReader reader)
       {
          // Properties
          w =  reader.ReadInt32();
          h =  reader.ReadInt32();
          x =  reader.ReadInt32();
          y =  reader.ReadInt32();
       
          // Elements
          {
             int size = reader.ReadInt32();
             if (size > 0)
             {
                 this.Elements = new Collection<DisplayElement>();
                 for(int i=0;i<size;i++){
                     DisplayElement o = new DisplayElement();
                     o.ReadBinary(reader);
                     this.AddElements(o);
                 }
             }
             else
             {
                 this.Elements = new Collection<DisplayElement>();
             }
          }
       }
       
       public void WriteBinary(BinaryWriter writer)
       {
          // Properties
          writer.Write(w);
          writer.Write(h);
          writer.Write(x);
          writer.Write(y);
       
          // Elements
          writer.Write(this.elements.Count);
          if (this.elements.Count > 0)
          {
              foreach (var col in this.elements)
                  col.WriteBinary(writer);
          }}
       
       
       /// <summary>
       /// Convertie l'instance en élément XML
       /// </summary>
       /// <param name="parent">Élément parent reçevant le nouveau noeud</param>
       /// <returns>Text XML du document</returns>
       public string ToXml(XmlElement parent)
       {
          XmlElement curMember = null;
          XmlDocument doc = null;
          // Element parent ?
          if (parent != null)
          {
              doc = parent.OwnerDocument;
          }
          else
          {
              doc = new XmlDocument();
              parent = doc.CreateElement("root");
              doc.AppendChild(parent);
          }
       
          //Ecrit au format XML
          XmlElement cur = doc.CreateElement("DisplayContent");
          parent.AppendChild(cur);
              
          //
          // Fields
          //
          
       		// Assigne le membre W
          curMember = doc.CreateElement("W");
          curMember.AppendChild(doc.CreateTextNode(w.ToString()));
          cur.AppendChild(curMember);
       
       		// Assigne le membre H
          curMember = doc.CreateElement("H");
          curMember.AppendChild(doc.CreateTextNode(h.ToString()));
          cur.AppendChild(curMember);
       
       		// Assigne le membre X
          curMember = doc.CreateElement("X");
          curMember.AppendChild(doc.CreateTextNode(x.ToString()));
          cur.AppendChild(curMember);
       
       		// Assigne le membre Y
          curMember = doc.CreateElement("Y");
          curMember.AppendChild(doc.CreateTextNode(y.ToString()));
          cur.AppendChild(curMember);
          
          //
          // Aggregations
          //
       
          // Elements
          {
             curMember = doc.CreateElement("Elements");
             if (this.elements.Count > 0)
             {
                 foreach (var col in this.elements)
                     col.ToXml(curMember);
             }
             cur.AppendChild(curMember);
          }
       
          parent.AppendChild(cur);
          return doc.InnerXml;
       }
       
       /// <summary>
       /// Initialise l'instance avec les données de l'élément XML
       /// </summary>
       /// <param name="element">Élément contenant les information sur l'objet</param>
       /// <remarks>Seuls les éléments existants dans le noeud Xml son importés dans l'objet</remarks>
       public void FromXml(XmlElement element)
       {
          foreach (XmlElement m in element.ChildNodes)
          {
              string property_value = m.InnerText.Trim();
              // charge les paramètres
              switch (m.Name)
              {
                //
                // Fields
                //
       
                // Assigne le membre W
                case "W":
                {
                   int value;
                   if(int.TryParse(property_value,out value)==false)
                      this.W = new Int32();
                   else
                      this.W = value;
                }
                break;
                // Assigne le membre H
                case "H":
                {
                   int value;
                   if(int.TryParse(property_value,out value)==false)
                      this.H = new Int32();
                   else
                      this.H = value;
                }
                break;
                // Assigne le membre X
                case "X":
                {
                   int value;
                   if(int.TryParse(property_value,out value)==false)
                      this.X = new Int32();
                   else
                      this.X = value;
                }
                break;
                // Assigne le membre Y
                case "Y":
                {
                   int value;
                   if(int.TryParse(property_value,out value)==false)
                      this.Y = new Int32();
                   else
                      this.Y = value;
                }
                break;
       
                //
                // Aggregations
                //
                
                // Assigne la collection Elements
                case "Elements":
                   {
                      foreach (XmlElement c in m.ChildNodes)
                      {
                         if("DisplayElement" == m.Name){
                             DisplayElement value = new DisplayElement();
                             value.FromXml(c);
                             this.AddElements(value);
                         }
                      }
                   }
                   break;
       			}
          }
       }
       
       #endregion // Serialization


      }

}