#include <stdio.h>
#include "ui.c"
#include <dirent.h> 

int main_page(){
    int walltype;
    char start_menu[][MAX_LENGTH] = {
        "Set Background",
        "Exit",
    };
     char title_text[] = 
        "   \033[32m_  _______      __     ____\n"
        "  | |/_/_  / | /| / /__ _/ / /\n"
        " _>  <_/_ <| |/ |/ / _ `/ / /\n"
        "/_/|_/____/|__/|__/\\_,_/_/_/\033[0m\n"
        "  wallpaper setting program\n"
        "   https://github.com/9JH1\n\n";
    char *answer = render_ui(start_menu, (sizeof(start_menu) / sizeof(start_menu[0])),title_text);
    if(strcmp(answer,"Set Background")==0){ 
        background_menu:
        char background_menu[][MAX_LENGTH] = {
            "Set IMAGE",
            "Set VIDEO",
            "back",
        };
        char *answer = render_ui(background_menu, (sizeof(background_menu) / sizeof(background_menu[0])),title_text);
        if(strcmp(answer,"back")==0){ 
            main_page();
        } else if(strcmp(answer,"Set IMAGE")){ 
            walltype=0;
        }else if(strcmp(answer,"Set VIDEO")){ 
            walltype=1;
        }
        char file_menu[][MAX_LENGTH]={
            "Show Files",
            "Enter a Path",
            "back",
        };
        file_handle:
            char *answer_file_menu = render_ui(file_menu, (sizeof(file_menu) / sizeof(file_menu[0])),title_text);
            if(strcmp(answer_file_menu,"back")==0){ 
                goto background_menu;
            } else if(strcmp(answer_file_menu,"Show Files")==0){ 
                DIR *d;
                struct dirent *dir;
                system("clear");
                d = opendir(".");
                if (d) {
                    while ((dir = readdir(d)) != NULL) {
                    printf("%s\n", dir->d_name);
                    }
                    closedir(d);
                }
                printf("press any key to continue...\n");
                take_single_char("");
                goto file_handle;
            } else if(strcmp(answer_file_menu,"Enter a Path")==0){ 
                system("clear");
                printf("%s",title_text);
                char *path = take_full_input("Enter Path: ",128);
                printf("Is this correct? '%s' [y/n]\n",path);
                int answer_yn = take_single_char("");
                if(answer_yn == 121){ 
                    char set_dialog[][MAX_LENGTH]={ 
                        "Set Wallpaper? ",
                        "Advanced Settings [WIP]",
                        "back",    
                    };
                    char *answer_set_dialog = render_ui(set_dialog,(sizeof(set_dialog)/sizeof(set_dialog[0])),title_text);
                    if(strcmp(answer_set_dialog,"back")==0){ 
                        goto file_handle;
                    } else if(strcmp(answer_set_dialog,"Advanced Settings [WIP]")) { 
                       char advanced_items_menu_VIDEO[][MAX_LENGTH]={
                        "Scale",
                        "Volume",
                        "Margins",
                        "Resolutions",
                       };
                       char advanced_items_menu_img[][MAX_LENGTH]={
                        "Scale",
                        "Pos Mode",
                       };
                       if(walltype==0){ 
                        //img
                        //char *video_advanced_dialog = render_ui(,(sizeof(set_dialog)/sizeof(set_dialog[0])),title_text);
                       } else { 
                        //video
                       }
                    }
                } else {
                    goto file_handle;
                }

            }
    } else { 
        system("clear");
        return 0;
    }
}


int main(){
    main_page();
    return 0;
}