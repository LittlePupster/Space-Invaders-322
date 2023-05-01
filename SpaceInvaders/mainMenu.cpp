#include "mainMenu.h"
using namespace std;	//Modified version of demo provided in class by professor
int displayMenu(){
  	initscr();
  	noecho();
  	cbreak();
  	curs_set(0);
  	WINDOW * menuwin = newwin(31, 40, 0, 5);
  	box(menuwin, 0, 0);
  	refresh();
  	wrefresh(menuwin);
  	keypad(menuwin, true);
  	const char * choices[2];
  	choices[0] = "Start New Game                ";
  	choices[1] = "Exit                          ";
  	int choice;
  	int highlight = 0;
	mvwprintw(menuwin,1,1,"------------SPACE INVADERS------------");	

	ifstream infile("highScores.txt");
	vector<int> scores;
	int score;
	while(infile >> score){
		scores.push_back(score);
	}
	mvwprintw(menuwin,2,1,"HIGHSCORES:");
	mvwprintw(menuwin,3,1,"1.)%d",scores[0]);
	mvwprintw(menuwin,4,1,"2.)%d",scores[1]);
	mvwprintw(menuwin,5,1,"3.)%d",scores[2]);
	mvwprintw(menuwin,6,1,"--------------------------------------");
	mvwprintw(menuwin,8,1,"   V V V V         V   V             ");
	mvwprintw(menuwin,10,1,"   V V     V  V   V V               ");
	mvwprintw(menuwin,12,1,"   |     |        |                 ");
	mvwprintw(menuwin,18,1,"       |      |                     ");
	mvwprintw(menuwin,20,1,"  |                   |             ");
	mvwprintw(menuwin,23,1,"     A");
	mvwprintw(menuwin,24,1,"--------------------------------------");
	mvwprintw(menuwin,25,1,"Press up/down keys to highlight and");
	mvwprintw(menuwin,26,1,"enter to select option");
  	while(1){
    		for(int i = 0; i < 2; i++){
      			if(i == highlight){
        			wattron(menuwin, A_REVERSE);
      			}
      			mvwprintw(menuwin, i + 28, 1, choices[i]);
      			wattroff(menuwin, A_REVERSE);
    		}
    		choice = wgetch(menuwin);
    		switch(choice){
      		case KEY_UP:
        		highlight--;
        		if(highlight == -1){
          			highlight = 0;
        			}
        		break;
      		case KEY_DOWN:
        		highlight++;
        		if(highlight == 2){
          			highlight = 1;
        		}
        		break;
      		default:
        		break;
    		}
    		if(choice == 10){
      			break;
    			}
  		}
  	if(highlight == 0){
	 	endwin();
	  	return 1;
  	}
  	if(highlight == 1){
		endwin();
		return -1;
  	}
	return 0;
}
void endMenu(int score){
        initscr();
        noecho();
        cbreak();
        curs_set(0);
        WINDOW * end = newwin(30, 40, 0, 5);
        box(end, 0, 0);
        refresh();
        wrefresh(end);
	mvwprintw(end, 1,1,"--------------GAME OVER---------------");
	mvwprintw(end,2,1,"Final score: %d",score);
	mvwprintw(end,28,1,"Press space to continue.");
	wrefresh(end);
	while(getch() != ' '){}
	endwin();
}

