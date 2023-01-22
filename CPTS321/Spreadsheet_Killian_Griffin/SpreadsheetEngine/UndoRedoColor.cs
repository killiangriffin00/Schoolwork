// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Class containing information for <see cref="Cell"/> class to execute
    /// an undo or redo command on its text property.
    /// </summary>
    public class UndoRedoColor : UndoRedoCommand
    {
        private readonly uint color;


        /// <summary>
        /// Initializes a new instance of the <see cref="UndoRedoColor"/> class.
        /// </summary>
        /// <param name="undoRedoCells">
        /// Denotes the cells that are affected by the undo/redo operation.
        /// </param>
        /// <param name="color">
        /// Denotes the color that the command instructs the <see cref="Cell"/> class
        /// to apply.
        /// </param>
        public UndoRedoColor(List<Cell> undoRedoCells, uint color)
        : base(undoRedoCells, "last cell color edit...")
        {
            this.color = color;
        }

        /// <summary>
        /// Gets the color that the command instructs the <see cref="Cell"/> class
        /// to apply.
        /// </summary>
        public uint Color
        {
            get { return this.color; }
        }

        /// <inheritdoc/>
        protected override UndoRedoCommand Inverse(Delegate[] references)
        {
            List<Cell> referencedNodes = new List<Cell>();
            foreach (Delegate reference in references.Skip(1))
            {
                referencedNodes.Add((Cell)reference.Target);
            }
            return new UndoRedoColor(referencedNodes, ((Cell)references[1].Target).BGColor);
        }
    }
}
