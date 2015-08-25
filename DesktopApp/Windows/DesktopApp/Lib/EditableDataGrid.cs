using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows.Input;

namespace Lib
{
    public class EditableDataGrid : DataGrid
    {
        public EditableDataGrid()
        {
            this.ClipboardCopyMode = DataGridClipboardCopyMode.None;// Customize les operations de Copier/Coller
            this.CellEditEnding += EditableDataGrid_CellEditEnding;
            this.BeginningEdit += EditableDataGrid_BeginningEdit;
            this.RowEditEnding += EditableDataGrid_RowEditEnding;
            this.PreviewKeyDown += EditableDataGrid_PreviewKeyDown;
        }

        ~EditableDataGrid()
        {
            this.CellEditEnding -= EditableDataGrid_CellEditEnding;
            this.BeginningEdit -= EditableDataGrid_BeginningEdit;
            this.RowEditEnding -= EditableDataGrid_RowEditEnding;
            this.PreviewKeyDown -= EditableDataGrid_PreviewKeyDown;
        }

        bool EditMode = false;

        void EditableDataGrid_CellEditEnding(object sender, DataGridCellEditEndingEventArgs e)
        {
            if (e.EditAction == DataGridEditAction.Cancel)
                return;

            if (e.Row.Item is IEntity)
            {
                IEntity entity = e.Row.Item as IEntity;
                if (entity.EntityState == EntityState.Added)
                    return;
                entity.EntityState = EntityState.Modified;
            }
        }

        void EditableDataGrid_BeginningEdit(object sender, DataGridBeginningEditEventArgs e)
        {
            this.EditMode = true;

            if (e.Row.IsNewItem && e.Row.Item is IEntity)
            {
                IEntity entity = e.Row.Item as IEntity;
                entity.EntityState = EntityState.Added;
            }
        }

        private void EditableDataGrid_RowEditEnding(object sender, DataGridRowEditEndingEventArgs e)
        {
            this.EditMode = false;

            if (e.Row.Item is IEntity)
            {
                IEntity entity = e.Row.Item as IEntity;
                //notify
                ICommand cmd = ViewModelBase.FindParentCommand(this, "EntityChange");
                if (cmd != null && cmd.CanExecute(entity))
                    cmd.Execute(entity);
            }
        }

        private void EditableDataGrid_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete && this.SelectedItem != null && this.EditMode == false)
            {
                if (this.SelectionMode == DataGridSelectionMode.Extended && this.SelectedItems != null)
                {
                    foreach (var item in this.SelectedItems)
                    {
                        IEntity entity = item as IEntity;
                        if (entity != null)
                        {
                            entity.EntityState = EntityState.Deleted;
                            //notify
                            ICommand cmd = ViewModelBase.FindParentCommand(this, "EntityChange");
                            if (cmd != null && cmd.CanExecute(entity))
                                cmd.Execute(entity);
                        }
                    }
                }
                else
                {
                    IEntity entity = this.SelectedItem as IEntity;
                    if (entity != null)
                    {
                        entity.EntityState = EntityState.Deleted;
                        //notify
                        ICommand cmd = ViewModelBase.FindParentCommand(this, "EntityChange");
                        if (cmd != null && cmd.CanExecute(entity))
                            cmd.Execute(entity);
                    }
                }
            }

            if (e.Key == Key.C && e.KeyboardDevice.Modifiers == ModifierKeys.Control && this.SelectedItem != null && this.EditMode == false)
            {
                if (this.SelectedItem != null)
                {
                    IEntity entity = this.SelectedItem as IEntity;
                    if (entity != null)
                    {
                        //command
                        ICommand cmd = ViewModelBase.FindParentCommand(this, "EntityCopy");
                        if (cmd != null && cmd.CanExecute(entity))
                            cmd.Execute(entity);
                    }
                }
            }

            if (e.Key == Key.V && e.KeyboardDevice.Modifiers == ModifierKeys.Control && this.SelectedItem != null && this.EditMode == false)
            {
                //command
                ICommand cmd = ViewModelBase.FindParentCommand(this, "EntityPaste");
                if (cmd != null && cmd.CanExecute(null))
                    cmd.Execute(null);
            }
        }
    }
}
