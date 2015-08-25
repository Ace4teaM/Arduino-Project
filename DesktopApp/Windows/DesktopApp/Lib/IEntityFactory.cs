using System;
using System.Collections;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Text;

namespace Lib
{
    public interface IEntityFactory
    {
        string Name { get; }
        IEntity GetReference(IEntity e);
        IEnumerable Factory<T>() where T : IEntity, new();
        void Commit(IEntity[] entities);
        List<IEntity> GetReferences();
        object QueryScalar(string query);
        int Query(string query);
        void Query(string query, Func<DbDataReader, int> act);
        void QueryObject(string query, object obj);
        string ParseType(object value);
    }
}