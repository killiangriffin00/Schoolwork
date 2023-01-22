// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    /// <summary>
    /// Node in <see cref="ExpressionTree"/> representing a
    /// subtract operator between two nodes.
    /// </summary>
    internal class OperatorNodeSubtract : OperatorNode
    {
        /// <summary>
        /// Gets the order in which the operator
        /// is to be executed.
        /// </summary>
        public override int Precedence => 0;

        /// <summary>
        /// Gets the associativity of the operator.
        /// 1 = left associative, 0 = right associative.
        /// </summary>
        public override int Associativity => 1;

        /// <summary>
        /// Gets character representing operator of the class.
        /// </summary>
        public override char OperatorChar => '-';

        /// <summary>
        /// Initializes a new instance of the <see cref="OperatorNodeSubtract"/> class.
        /// </summary>
        /// <param name="left">
        /// Denotes the left node of the operation.
        /// </param>
        /// <param name="right">
        /// Denotes the right node of the operation.
        /// </param>
        public OperatorNodeSubtract(Node left, Node right)
            : base(left, right)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="OperatorNodeSubtract"/> class.
        /// </summary>
        public OperatorNodeSubtract()
            : base()
        {
        }

        /// <summary>
        /// Implementation of abstract parent operate method
        /// for subtraction operator.
        /// </summary>
        /// <returns>
        /// <see cref="double"/> representing difference of left 
        /// and right nodes.
        /// </returns>
        public override double Operate()
        {
            return this.Left.GetValue() - this.Right.GetValue();
        }
    }
}
