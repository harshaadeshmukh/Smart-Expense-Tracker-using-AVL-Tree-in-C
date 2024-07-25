# 📊 Smart Expense Tracker
Smart Expense Tracker is a robust console application designed for efficient personal expense management. Leveraging the power of AVL Trees, this application maintains a balanced data structure to ensure optimal performance for various operations, including adding, viewing, deleting, searching, and saving expense records.

# 🔍 Features
- **Add Expense**: Record new expenses with details such as date, category, amount, and description. You can choose between using the current date or specifying a custom date.
- **View Expenses**: Display all recorded expenses in a structured format, showing ID, date, category, amount, and description.
- **Delete Expense**: Remove an expense record by its unique ID, with automatic rebalancing of the AVL Tree to maintain performance.
- **Search Expenses**: Find and display expenses based on date and category, with case-insensitive matching.
- **Save & Load Data**: Save expenses to a text file and load them back into the application to persist data between sessions.
- **Efficient Data Management**: Utilizes AVL Trees to ensure balanced tree structure, providing fast insertions, deletions, and lookups.


# 📂 How It Works
The application uses AVL Trees, a self-balancing binary search tree, to manage expense records. Each node in the AVL Tree contains:

- **ID**: A unique identifier for each expense.
- **Date**: The date of the expense.


- **Category**: The category of the expense.
- **Amount**: The amount spent.
- **Description**: A textual description of the expense.


Operations on the AVL Tree, such as insertion and deletion, are performed with automatic rebalancing to maintain tree height and ensure efficient performance. 
The application also includes a loading animation and a user-friendly console interface to enhance the user experience.

# 📖 Usage
- **Add an Expense**: Follow the prompts to enter details and choose the date.
- **View Expenses**: Access the list of all recorded expenses.
- **Delete an Expense**: Specify the ID of the expense to be deleted.
- **Search for Expenses**: Provide a date and category to find specific records.
- **Save and Exit**: Save changes to the text file before exiting the application.

# 📄 License
This project is licensed under the MIT License.

# 🤝 Contributing
Contributions are welcome! Please fork the repository and submit pull requests for any improvements or bug fixes.

# 📫 Contact
For any questions or feedback, feel free to reach out via GitHub issues or directly contact harshad.deshmukh82004@gmail.com.
