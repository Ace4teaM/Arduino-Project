using System;
using System.IO;
using System.Text;
using System.Xml;

namespace Lib
{
    public interface IEntitySerializable
    {
        void ReadBinary(BinaryReader reader);
        void WriteBinary(BinaryWriter writer);
        void FromXml(XmlElement element);
        string ToXml(XmlElement parent);
    }
}