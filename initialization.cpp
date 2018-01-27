void initialization (int row[],int column[])
{
	int basecount;
	basecount=rand()%4 + 1;
	int emptybase;
	if (basecount<=2)
	{
		emptybase=2;
	}
	else
	{
		emptybase=3;
	}
	int counter=0;
	int ibase;
	int jbase;
	int basechack[3][5];
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<5;j++)
		{
			basechack[i][j]=0;
		}
	}
	while(counter<2*basecount+emptybase)
	{	while(true)
		{
		ibase=rand()%3;
		jbase=rand()%5;
		if (basechack[ibase][jbase]==0)
		{
			basechack[ibase][jbase]=1;
			break;
		}
		}
		if (counter<emptybase)
		{
			base[counter].type="e";
			base[counter].x=row[ibase];
			base[counter].y=column[jbase];
		}
		else
		{
			if (counter%2==0)
			{
				base[counter].type="m";
				base[counter].x=row[ibase];
				base[counter].y=column[jbase];
			}
			else
			{
				base[counter].type="f";
				base[counter].x=row[ibase];
				base[counter].y=column[jbase];
			}
		}
		counter++;
	}	

}