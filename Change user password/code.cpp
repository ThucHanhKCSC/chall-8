#include <iostream>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
 
 
void SetStdinEcho(bool enable = true){
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
        if( !enable )
            tty.c_lflag &= ~ECHO;
        else
            tty.c_lflag |= ECHO;
 
    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
 
int SearchForUserName(const char *username){
    int found = 0;
    
    while (true) {
            errno = 0;
            passwd* entry = getpwent();
            if (!entry) {
                if (errno) {
                    std::cerr << "ERROR";
                    return EXIT_FAILURE;
                }
                break;
            }
            if(!strcmp(username, entry->pw_name)){
                found = 1;
                break;
            }
        }
        endpwent();
 
    return found;
}
 
 
int main(){
    char username[30], password[30], password2[30];
    
    std::cout << "Nhap vao ten user muon thay doi password: ";
    std::cin.get(username, 30);
    
    int found = SearchForUserName(username);
    
    if(!found){
        std::cout << "\nUser " << username << " khong ton tai trong database\n";
    }
    else{
        std::cout << "\nNhap vao password moi cho user: ";
        SetStdinEcho(false);
        std::cin.get();
        std::cin.get(password, 30); 
        SetStdinEcho(true);
        std::cout << "\nNhap lai password moi: ";
        SetStdinEcho(false);
        std::cin.get();
        std::cin.get(password2, 30);
        SetStdinEcho(true);
        std::cout << "\n";
        if(!strcmp(password, password2)){
            char command[100] = "sudo usermod -p $(openssl passwd -crypt ";
            strcat(command, password);
            strcat(command, ") ");
            strcat(command, username);
 
            int result = system(command);
            if(!result)
                std::cout << "\nCap nhat password thanh cong\n";
            else
                std::cout << "\nCap nhat that bai\n";
        }
        else{
            std::cout << "\nThat bai do password nhap lai khong trung voi password moi\n";
        }
    }
    return 0;
}
