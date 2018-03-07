 int update()
 {
 
 if (up && page == 1 ) {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=3;
    }      
  }else if (up && page == 2 ) {
    up = false;
    contrast--;
    setContrast();
  }


  if (down && page == 1) {
    down = false;
    menuitem++;
    if (menuitem==4) 
    {
      menuitem=1;
    }      
  }else if (down && page == 2 ) {
    down = false;
    contrast++;
    setContrast();
  }


  if (middle) {
    middle = false;
    
    if (page == 1 && menuitem==2) 
    {
      if (backlight) 
      {
        backlight = false;
        turnBacklightOff();
        }
      else 
      {
        backlight = true; 
        turnBacklightOn();
       }
    }

    if(page == 1 && menuitem ==3)
    {
      resetDefaults();
    }


else if (page == 1 && menuitem==1) {
      page=2;
     }
else if (page == 2) {
      page=1;
     }
   }
 }
   
