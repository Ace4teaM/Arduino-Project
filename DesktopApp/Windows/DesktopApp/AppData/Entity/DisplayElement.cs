/*
   Extension de la classe d'entité DisplayElement

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

    public partial class DisplayElement : IEntity, ISerializable, IEntitySerializable    {
         #region Constructor
         public DisplayElement(){
            // w
            this.w = new Int32();
            // h
            this.h = new Int32();
            // x
            this.x = new Int32();
            // y
            this.y = new Int32();
            // z
            this.z = new Int32();
         }
         
         public DisplayElement(int w, int h, int x, int y, int z) : this(){
            this.w = w;
            this.h = h;
            this.x = x;
            this.y = y;
            this.z = z;
         }
         #endregion // Constructor
         
          public string EntityName { get{ return "DisplayElement"; } }

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
         // Profondeur
         protected int z;
         public int Z { get{ return z; } set{ z = value; } }
         #endregion // Fields

         #region Associations
         // 
         protected DisplayContent content;
         public virtual DisplayContent Content { get{ return content; } set{ content = value; } }
         #endregion // Associations

         #region Methods
         public override string ToString()
         {
             string result = this.GetType().Name+":"+Environment.NewLine+"-----------------------------"+Environment.NewLine;
             result += "w = " + w + Environment.NewLine;
             result += "h = " + h + Environment.NewLine;
             result += "x = " + x + Environment.NewLine;
             result += "y = " + y + Environment.NewLine;
             result += "z = " + z + Environment.NewLine;
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
            info.AddValue("z", z, typeof(int));
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
          z =  reader.ReadInt32();
       }
       
       public void WriteBinary(BinaryWriter writer)
       {
          // Properties
          writer.Write(w);
          writer.Write(h);
          writer.Write(x);
          writer.Write(y);
          writer.Write(z);}
       
       
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
          XmlElement cur = doc.CreateElement("DisplayElement");
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
       
       		// Assigne le membre Z
          curMember = doc.CreateElement("Z");
          curMember.AppendChild(doc.CreateTextNode(z.ToString()));
          cur.AppendChild(curMember);
          
          //
          // Aggregations
          //
       
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
                // Assigne le membre Z
                case "Z":
                {
                   int value;
                   if(int.TryParse(property_value,out value)==false)
                      this.Z = new Int32();
                   else
                      this.Z = value;
                }
                break;
       
                //
                // Aggregations
                //
                
       			}
          }
       }
       
       #endregion // Serialization


      }

}