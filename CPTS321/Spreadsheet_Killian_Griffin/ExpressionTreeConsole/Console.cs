namespace Console
{
    using System;

    class Console
    {
        private string header;

        private SpreadsheetEngine.ExpressionTree tree;

        public Console()
        {
            tree = new SpreadsheetEngine.ExpressionTree();

            while (true)
            {
                string input = string.Empty;
                this.header = "---|Expression Tree Console App|---";

                ClearConsole();
                System.Console.Write("Menu:\n");
                System.Console.Write("1. Enter a new expression\n");
                System.Console.Write("2. Set a variable value\n");
                System.Console.Write("3. Evaluate Tree\n");
                System.Console.Write("4. Quit\n");
                System.Console.Write("--:");

                input = System.Console.ReadLine();
                switch (input)
                {
                    case "1":
                        enterExpression();
                        break;

                    case "2":
                        setVariable();
                        break;

                    case "3":
                        EvaluateTree();
                        break;

                    case "4":
                        break;
                }
            }
        }

        /// <summary>
        /// Assigns header string for console. Setter ensures
        /// consistent header for console application.
        /// </summary>
        public string Header
        {
            get
            {
                return this.header;
            }

            set
            {
                this.header = value;
                this.ClearConsole();
            }
        }

        private void enterExpression()
        {
            string expression = string.Empty;
            this.Header = "----------| Enter New Expression| ----------";
            this.ClearConsole();

            System.Console.Write("Enter an expression name: \n");
            System.Console.Write("--:");
            expression = System.Console.ReadLine();
            tree = new SpreadsheetEngine.ExpressionTree(expression);
            System.Console.Clear();
        }

        private void setVariable()
        {
            string variableName = string.Empty;
            double variableValue = 0;
            this.Header = "----------|Enter New Variable|----------";

            System.Console.Write("Enter a variable name: \n");
            System.Console.Write("--:");
            variableName = System.Console.ReadLine();
            ClearConsole();
            System.Console.Write("Enter a variable value: \n");
            System.Console.Write("--:");
            variableValue = double.Parse(System.Console.ReadLine());
            tree.SetVariable(variableName, variableValue);
        }

        private void EvaluateTree()
        {
            string variableName = string.Empty;
            this.Header = "-----------|Tree Evaluation|------------";

            System.Console.Write(tree.Evaluate().ToString());
            System.Console.Write("\n");
            System.Console.Write("--:");
            variableName = System.Console.ReadLine();
            System.Console.Clear();
        }

        /// <summary>
        /// Clears console text and maintians header.
        /// </summary>
        private void ClearConsole()
        {
            System.Console.Clear();
            System.Console.Write(this.header);
            System.Console.Write("\n");
        }

        public static void Main()
        {
            Console mainConsole = new Console();
        }
    }
}