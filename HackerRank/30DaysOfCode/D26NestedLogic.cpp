#include <stdio.h>

int main()
{
    int rd, rm, ry;
    int dd, dm, dy;
    scanf("%d %d %d", &rd, &rm, &ry );
    scanf("%d %d %d", &dd, &dm, &dy );

    int fine;

    if((rd<=dd&&rm==dm&&ry==dy) || (rm<dm&&ry<=dy)||(ry<dy))
    fine = 0;
    else if(rm==dm&&ry==dy)
        fine = 15*(rd-dd);    
    else if(ry==dy)
        fine = 500*(rm-dm);    
    else
        fine = 10000;
    printf("%d", fine);

   return 0; 
}