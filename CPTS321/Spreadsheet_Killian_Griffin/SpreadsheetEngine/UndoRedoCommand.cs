// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    using System.ComponentModel;

    /// <summary>
    /// Class containing information for <see cref="Cell"/> class to execute
    /// an undo or redo command.
    /// </summary>
    public abstract class UndoRedoCommand
    {
        private readonly string commandDescription;

        /// <summary>
        /// Initializes a new instance of the <see cref="UndoRedoCommand"/> class.
        /// </summary>
        /// <param name="undoRedoCells">
        /// Denotes the cells that are affected by the undo/redo operation.
        /// </param>
        /// <param name="commandDescription">
        /// Denotes the displayed text on the menu in the application interface for
        /// the command.
        /// </param>
        public UndoRedoCommand(List<Cell> undoRedoCells, string commandDescription)
        {
            foreach (Cell cell in undoRedoCells)
            {
                this.UndoRedo += cell.UndoRedoEventHandler;
            }

            this.commandDescription = commandDescription;
        }

        /// <summary>
        /// Event that conatins the handler functions all <see cref="Cell"/>s affected by
        /// the undo/redo command.
        /// </summary>
        public event EventHandler UndoRedo = (sender, e) => { };

        /// <summary>
        /// Gets the displayed command description.
        /// </summary>
        public string CommandDescription
        {
            get { return this.commandDescription; }
        }

        /// <summary>
        /// Executes the handler functions of the <see cref="UndoRedo"/>
        /// event.
        /// </summary>
        public void DoUndoRedo()
        {
            this.UndoRedo(this, new EventArgs());
        }

        /// <summary>
        /// Gets an <see cref="UndoRedoCommand"/> rpersenting the current
        /// state of the <see cref="Cell"/>s that the command is referencing.
        /// Used for setting reverse operations.
        /// </summary>
        /// <returns>
        /// <see cref="UndoRedoCommand"/> reprsenting the current
        /// state of the <see cref="Cell"/>s that the command is referencing.
        /// </returns>
        public UndoRedoCommand GetInverse()
        {
            return Inverse(this.UndoRedo.GetInvocationList());
        }

        /// <summary>
        /// Abstract function reprsenting the current
        /// state of the <see cref="Cell"/>s that the command is referencing.
        /// </summary>
        /// <param name="references">
        /// <see cref="Delegate"/>s referencing the <see cref="Cell"/>s of the
        /// stored handler functions.
        /// </param>
        /// <returns>
        /// <see cref="UndoRedoCommand"/> reprsenting the current
        /// state of the <see cref="Cell"/>s that the command is referencing.
        /// </returns>
        protected abstract UndoRedoCommand Inverse(Delegate[] references);
    }
}
