// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Class containing information for <see cref="Cell"/> class to execute
    /// an undo or redo command on its text property.
    /// </summary>
    public class UndoRedoText : UndoRedoCommand
    {
        private readonly string text;

        /// <summary>
        /// Initializes a new instance of the <see cref="UndoRedoText"/> class.
        /// </summary>
        /// <param name="undoRedoCells">
        /// Denotes the cells that are affected by the undo/redo operation.
        /// </param>
        /// <param name="text">
        /// Denotes the text that the command instructs the <see cref="Cell"/> class
        /// to apply.
        /// </param>
        public UndoRedoText(List<Cell> undoRedoCells, string text)
        : base(undoRedoCells, "last cell text edit...")
        {
            this.text = text;
        }

        /// <summary>
        /// Gets the text that the command instructs the <see cref="Cell"/> class
        /// to apply.
        /// </summary>
        public string Text
        {
            get { return this.text; }
        }

        /// <inheritdoc/>
        protected override UndoRedoCommand Inverse(Delegate[] references)
        {
            List<Cell> referencedNodes = new List<Cell>();
            foreach (Delegate reference in references.Skip(1))
            {
                referencedNodes.Add((Cell)reference.Target);
            }
            return new UndoRedoText(referencedNodes, ((Cell)references[1].Target).Text);
        }
    }
}
