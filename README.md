# <div align="center">⚙️ pipex (a [42](https://42perpignan.fr/) project) ⚙️</div>
## 📑 Introduction
School 42's `pipex` project challenges students to rebuild a shell like pipe in the C language.\
To do so, students need to have a thorough understanding of input/output redirections, processes creation and manipulation, as well as memory leaks management and using the environment to extract variables such as `$PATH`  for command execution.
As a bonus, we can obtionally handle multiple pipes and code a [**here document**](https://tldp.org/LDP/abs/html/here-docs.html) implementation, reading standard input while waiting for the user to write the contents of a dummy file.\
Personally, I love this project because of all the new concepts it introduces. And it's a excellent introduction to the future [**42-minishell**](https://github.com/Floperatok/42-minishell) project, where we'll have to create a bash clone.

Subject : <a href=asset/en.subject.pdf>en.pipex_subject.pdf<a/>
### My grade
[![nsalles's 42 pipex Score](https://badge42.coday.fr/api/v2/clshyl91d071301p436jjiyqr/project/3402523)](https://github.com/Coday-meric/badge42)
## Usage
Download `pipex` and enter the repo :
```sh
git clone https://github.com/Floperatok/42-pipex.git && cd 42-pipex
```
Compile the project :
```sh
make && make clean
```
Create a file as the input and execute pipex :
```sh
./pipex your_input_file "command1" "command2" output_file
```
In this configuration, `pipex` will read the content of your input file and pass it through the two commands, then write the result to the output file.\
*Note that you can use as many commands as you like (starting from 2)*

A typical exemple of pipex use :
```sh
echo "hello world" > input_file && ./pipex input_file "cat -e" "rev" output_file
```
You can use the [**here document**](https://tldp.org/LDP/abs/html/here-docs.html) feature using the following command :
```sh
./pipex here_doc EOF "command1" "command2" output_file
```
Where `EOF` is the delimiter up to which the here document reads.