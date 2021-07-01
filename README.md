The objective of this project is for you to create a simple shell. This was a group project with Sanne Albreghs.

**Subject:**

Your shell should:
- show a prompt when waiting for a new command.
- Search and launch the right exectuable (based on the PATH variable or by using relative or absolute path) like in bash.
- It must implement the builtins like in bash:
  - **echo** with option '-n'
  - **cd** with only a relative or absolute path
  - **pwd** without any options
  - **export** without any options 
  - **unset** without any options
  - **env** without any options and any arguments
  - **exit** without any options
- ; in the command should seperate commands like in bash
- ' and " should work like in bash except for multiline commands
- Redirections < > ">>" should work like in bash except for file descriptor aggregation
- pipes | should work lik ein bash
- Environment variables ($ followed by characters) should work like in bash
- $? should work like in bash
- ctrl-C, ctrl-D, and ctrl-\ should have the same result as in bash
 
**Usage:**

Make to compile as seen below

![Screenshot 2021-06-30 at 19 17 37](https://user-images.githubusercontent.com/61982496/124004353-32994180-d9d8-11eb-9679-2de374786b3e.png)


**Testing:**

To test run the program and compare your results with bash.
An example can be seen below

![Screenshot 2021-06-30 at 19 18 00](https://user-images.githubusercontent.com/61982496/124004233-1bf2ea80-d9d8-11eb-86c8-beaadc3a1988.png)

Suceeded with 100/100
