# Educational Management System

## Introduction
The system allows course management through different user profiles (Student, Teacher, Director). It includes a login and specific submenus for each role, where users can perform actions according to their functions.

## Detailed System Description
The main objective of the program is to manage the course regardless of the user's role in the institution. The user hierarchy is as follows:

1. Administrator
2. Director
3. Teacher
4. Student

The first time the application is accessed, an "Administrator" user is used. This option is essential to proceed correctly in the program's workflow. A "File Number" is automatically generated, and a numeric "password" is required. Authentication data is securely stored in `.dat` files.

### Features by Role

#### Administrator
- **Profile Management:**
  - Create, activate, and deactivate Director profiles.
  - Reset passwords for Directors, Teachers, and Students.
  - Change the current user's password.
- **Backup Management:**
  - Create and restore backups of all files.

#### Director
- **Profile Management:**
  - Create, activate, and deactivate Teacher and Student profiles.
- **Curriculum Management:**
  - Add subjects, assign teachers, and view the curriculum.
- **Notice Management:**
  - Create and view notices.
- **Change the current user's password.**

#### Teacher
- **Subject Management:**
  - View assigned subjects, create and view final exams, enter grades.
- **Lists:**
  - View lists of enrolled, approved, and failed students.
- **View notices and change the current user's password.**

#### Student
- **Course Management:**
  - View schedules, enroll and drop subjects, register for and view final exams.
  - View the curriculum and notices.
  - Change the current user's password.

## Class Diagram
![Class Diagram](sistema_gestion/images/diagrama.png)

## Installation and Usage
1. Clone the repository:
    ```bash
    git clone https://github.com/AlejoLg1/SGE.git
    ```
2. Compile and Run the Project via an IDE:
    
    - Open your preferred Integrated Development Environment (IDE), such as Visual Studio Code, Code::Blocks, Eclipse, or others.
    - Load the cloned project (SGE) into the IDE.
    - Configure the project according to the specific setup instructions for each IDE.
    - Compile and run the project using the functions provided by your IDE.
      
3. Follow On-Screen Instructions:
    - Once the project is successfully compiled and executed, follow the on-screen instructions to interact with the system according to the specified user role.

## License
This project is licensed under the terms of the MIT license.
