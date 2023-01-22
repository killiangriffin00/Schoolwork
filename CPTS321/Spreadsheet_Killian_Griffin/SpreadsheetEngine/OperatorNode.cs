// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Represents an operator in the <see cref="ExpressionTree"/>
    /// combining two values.
    /// </summary>
    public abstract class OperatorNode : Node
    {
        /// <summary>
        /// Gets the order in which the operator
        /// is to be executed.
        /// </summary>
        public abstract int Precedence { get; }

        /// <summary>
        /// Gets the associativity of the operator.
        /// 1 = left associative, 0 = right associative.
        /// </summary>
        public abstract int Associativity { get; }

        /// <summary>
        /// Gets character representing the operator of the class.
        /// </summary>
        public abstract char OperatorChar { get; }

        /// <summary>
        /// Initializes a new instance of the <see cref="OperatorNode"/> class.
        /// </summary>
        /// <param name="left">
        /// Denotes the left node of the operation.
        /// </param>
        /// <param name="right">
        /// Denotes the right node of the operation.
        /// </param>
        public OperatorNode(Node left, Node right)
        {
            this.Left = left;
            this.Right = right;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="OperatorNode"/> class.
        /// </summary>
        public OperatorNode()
        {
        }

        /// <summary>
        /// Gets or sets the left property that represents the
        /// value of the left child node.
        /// </summary>
        public Node? Left { get; set; }

        /// <summary>
        /// Gets or sets the right property that represents the
        /// value of the right child node.
        /// </summary>
        public Node? Right { get; set; }

        /// <summary>
        /// Gives the result of the operator applied to the left
        /// and right properties. Operator is defined by child classes.
        /// </summary>
        /// <returns>
        /// <see cref="double"/> representing the result of the operation.
        /// </returns>
        public abstract double Operate();

        /// <summary>
        /// Parent class method for getting the evaluated
        /// value of the node subclass.
        /// </summary>
        /// <returns>
        /// <see cref="double"/> representing the evaluated value of the
        /// operation.
        /// </returns>
        public override double GetValue()
        {
            return this.Operate();
        }
    }
}
