# Audiobook Library System

## Overview

This project is an Audiobook Library System designed to manage users and audiobooks efficiently. The system focuses on efficient management of audiobooks and user interactions, including listening progress, library management, and user preferences. The implementation is done using the AVL tree data structure to ensure quick access and efficient management.

## Features

1. **User Management**
   - Add and manage user profiles with details such as user ID, name, email, and preferences.
   - Maintain a separate audiobook library for each user.

2. **Audiobook Management**
   - Add, edit, and delete audiobooks.
   - Maintain audiobook details like ID, title, author, narrator, duration, genre, and ratings.
   
3. **Library Management**
   - Add or remove audiobooks to/from the user's personal library.
   - Display user's library with filtering options.
   
4. **Listening Progress**
   - Track and update the user's listening progress for each audiobook.
   
5. **Rating System**
   - Allow users to rate audiobooks, contributing to an overall feedback score.
   
6. **Reports and Searches**
   - Search for audiobooks based on various criteria.
   - Generate reports for user's listening history and audiobook details.
   - Find the most popular audiobook based on ratings.
   - Perform range searches for audiobooks based on their IDs.
   - Merge libraries of two users.
   
## Implementation

### Data Structures
1. **User Tree**: An AVL tree to manage user profiles. Each node contains:
   - UserID
   - Name
   - Email
   - Preferences
   - Reference to the user's audiobook library (another AVL tree).

2. **Audiobook Tree**: An AVL tree to manage audiobooks. Each node contains:
   - AudiobookID
   - Title
   - Author
   - Narrator
   - Duration
   - Genre
   - Sum_Rating
   - Count_Rating

### Functions

1. **Add_audiobook() and Edit_audiobook()**
   - Add or modify audiobook details.
   
2. **Delete_audiobook()**
   - Delete an audiobook based on title and author.
   
3. **Add_user_profile()**
   - Create a new user profile.
   
4. **Add to User_library()**
   - Add or remove audiobooks to/from the user's library.
   
5. **Search_audiobook()**
   - Search audiobooks based on title, author, genre, etc.
   
6. **Listening_progress()**
   - Update the user's listening progress for an audiobook.
   
7. **Display_user_libraries()**
   - Display audiobooks in the user's library with filter options.
   
8. **Rate_Audiobook()**
   - Allow users to rate an audiobook.
   
9. **Most_popular_audiobook()**
   - Retrieve the most popular audiobook based on average rating.
   
10. **Listening_history_report_user()**
   - Generate a report of the user's listening history.
   
11. **Merge_user_libraries()**
   - Merge libraries of two users into one.
   
12. **Listening_history_report_audiobook()**
   - Generate a report of an audiobook's listening history.
   
13. **Range_Search_Audiobook()**
   - Search and print audiobook titles within a range of IDs.

### File Handling
- Data is read from and written to a `.txt` file.
- The file contains data for 5 users and 10 audiobooks and can be extended to any number of users

## How to Run

1. **Compile the Code**
   - Use a C compiler to compile the code, e.g., `gcc audiobook_library.c -o audiobook_library`.

2. **Run the Executable**
   - Execute the compiled file, e.g., `./audiobook_library`.

3. **Input Data**
   - Provide input data through a `.txt` file formatted as required.

4. **Interact with the System**
   - Follow the prompts to add, edit, or manage users and audiobooks.

## Notes

- Ensure that the email addresses are unique when creating user profiles.
- The audiobook library for each user is implemented as a tree, allowing efficient management.
- The system maintains data consistency by using AVL trees to keep the operations efficient and balanced.

## Conclusion

This Audiobook Library System provides a comprehensive solution for managing audiobooks and user interactions efficiently using AVL trees. It ensures quick access to data, effective tracking of user progress, and supports user libraries and preferences seamlessly.
