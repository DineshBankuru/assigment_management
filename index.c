#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
struct values
{
	float open; 
	float high;
	float low;
	float close;
	double volume;
};
struct company
{
	char name[20];
	struct values val;	
};
struct date
{
	struct company com[10];
};

//Question 1 ---> Find % change in the price of a stock from start to end date

void per_change(struct date dates[],int comp_num,int last_date)
{
	float a;
	a=(( dates[last_date].com[comp_num].val.close - dates[0].com[comp_num].val.open ) / dates[0].com[comp_num].val.open);
	a=a*100;
	printf("\n Percentage change in the price of %s stock from start to end date is %f",dates[0].com[comp_num].name,a);
}
// Ques 2

void sort_close(struct date dates[],int day,int j,float temp_vol[],float temp_close[])
{
	float k;
	if(temp_close[j]>temp_close[j+1])
	{
		k=temp_close[j];
		temp_close[j]=temp_close[j+1];
		temp_close[j+1]=k;
		
		k=temp_vol[j];
		temp_vol[j]=temp_vol[j+1];
		temp_vol[j+1]=k;
	}		
}

void sort_vol(struct date dates[],int day)
{
	int i,j;
	float temp_vol[10];
	float temp_close[10];
	for(i=0;i<10;i++)
	{
		temp_vol[i]=0;
		temp_close[i]=0;
	}
	for(i=0;i<10;i++)
	{
		temp_vol[i]=dates[0].com[i].val.volume;
		temp_close[i]=dates[0].com[i].val.close;
	}
	int sorted=0;float k;
	for(i=0;i<9 && sorted==0 ;i++)
	{
		sorted=1;
		for(j=0;j<9-i;j++)
		{
		    if(temp_vol[j]==temp_vol[j+1])
			{
				sort_close(dates,day,j,temp_vol,temp_close);
				sorted=0;
			}
			else if(temp_vol[j]>temp_vol[j+1])
			{
				k=temp_close[j];
				temp_close[j]=temp_close[j+1];
				temp_close[j+1]=k;
		
				k=temp_vol[j];
				temp_vol[j]=temp_vol[j+1];
				temp_vol[j+1]=k;
				sorted=0;
			}
		}
	}
	for(i=0;i<10;i++)
	{
	    printf("%f   %f\n",temp_vol[i],temp_close[i]);
	}
	printf("Sr.No\t\tCompany\t\tOpen\t\t\thigh\t\t\tlow\t\t\tclose\t\t\tvolume\n\n");
	for(i=0;i<=9;i++)
	{
		for(j=0;j<=9;j++)
		{
			if(temp_vol[i]==dates[0].com[j].val.volume && temp_close[i]==dates[0].com[j].val.close)
			{
				printf("%d\t\t%s\t\t%f\t\t%f\t\t%f\t\t%f\t\t%lf\n\n",i , dates[0].com[j].name , dates[0].com[j].val.open , dates[0].com[j].val.high , dates[0].com[j].val.low , dates[0].com[j].val.close , dates[0].com[j].val.volume);
				break;
			}
		}
	}
}

//Question 3 

void profit_loss(struct date dates[],int bought_day,int sold_day)
{
	int i;
	float a;
	for(i=0;i<=9;i++)
	{
		a=((dates[sold_day].com[i].val.close - dates[bought_day].com[i].val.open)/dates[bought_day].com[i].val.open)*100;
		if(a<0)
		{
			printf("\n%s company has loss when it bought on day %d and sold on day %d\n",dates[bought_day].com[i].name,bought_day,sold_day);
		}
		else if(a>0)
		{
			printf("\n%s company has profit when it bought on day %d and sold on day %d\n",dates[bought_day].com[i].name,bought_day,sold_day);
		}
		else
		{
			printf("\n%s company dosen't have profit or loss when it bought on day %d and sold on day %d\n",dates[bought_day].com[i].name,bought_day,sold_day);
		}
	}
}

// Question 4

void high_perform(struct date dates[] , int start , int end)
{
	int i,loc;
	float a,max=0;
	for(i=0;i<=9;i++)
	{
		a=(( dates[end].com[i].val.close-dates[start].com[i].val.open ) / dates[start].com[i].val.open ) *100;
		if(a>0 && a>max)
		{
			max=a;
			loc=i;
		}
	}
	printf("\n Highest performing stock is %s between day %d and %d \n",dates[end].com[loc].name,start,end);
}

//Question 5

void low_perform(struct date dates[] , int start , int end)
{
	int i,loc;
	float a,min;
	min=0;
	for(i=0;i<=9;i++)
	{
		a=(( dates[end].com[i].val.close - dates[start].com[i].val.open ) / dates[start].com[i].val.open ) *100;
		if(a<min)
		{
			min=a;
			loc=i;
		}
	}
	printf("\nLowest performing stock is %s between day %d and %d \n",dates[end].com[loc].name,start,end);
}

//Question 6
void overall_performance(struct date dates[] , int start , int end)
{
	int i,j;
	float sum,temp;
	float a[10],b[10];
	for(i=0;i<=9;i++)
	{
		sum=0;
		for(j=start;j<=end;j++)
		{
			sum += (( dates[j].com[i].val.open - dates[j-1].com[i].val.open ) / dates[j-1].com[i].val.open ) * 100 * dates[j].com[i].val.volume;
		}
		a[i]=sum;
		b[i]=sum;
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<9-i;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	printf("\n All stock as per increasing the overall performance ....\n\n");
	printf("Company\t\t\tOverall Performance\n");
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i]==b[j])
			{
				printf("%s\t\t\t%f\n",dates[end].com[j].name,a[i]);
			}
		}
	}
}

//Question 7 (a) ---> find the average value of all stock at any instant of time

float average_value(struct date dates[] , int day)
{
	int i;
	float volume_sum,sum;
	for(i=0;i<10;i++)
	{
		volume_sum += dates[day].com[i].val.volume;
		sum = dates[day].com[i].val.volume * dates[day].com[i].val.open;
	}
	return (sum/volume_sum);
	//printf("\nThe average value of all stock on day %d is %f",day,sum/volume_sum);
}

//Question 7 (b) ---> average of average values of all stocks from start to end date

void average(struct date dates[] , int last_date)
{
	int i;
	float sum=0;
	for(i=0;i<last_date;i++)
	{
		sum += average_value(dates,i);
	}
	printf("\naverage of average values of all stocks from day 0 to day %d is %f\n",last_date-1,sum/last_date);
}



int main()
{
	int first_date=0,last_date;
	//printf("\nEnter last date : \n");
	scanf("%d",&last_date);
	
	struct date dates[last_date];
	int i,j,k,l,m;
	
   
	for(i=0;i<last_date;i++)
	{
		//printf("->->->For Day %d\n",i);
		for(j=0;j<10;j++)
		{
			//printf("->->Details of company %d on day %d\n",j,i);
			//printf("Enter company name : ");
			scanf("%[^\n]%*c",dates[i].com[j].name);
			//printf("Enter open price of company %d on day %d : \n",j,i);
			scanf("%f",&dates[i].com[j].val.open);
			//printf("Enter high price of company %d on day %d : \n",j,i);
			scanf("%f",&dates[i].com[j].val.high);
			//printf("Enter low price of company %d on day %d : \n",j,i);
			scanf("%f",&dates[i].com[j].val.low);
			//printf("Enter close price of company %d on day %d : \n",j,i);
			scanf("%f",&dates[i].com[j].val.close);
			//printf("Enter volume price of company %d on day %d : \n",j,i);
			scanf("%lf",&dates[i].com[j].val.volume);
		}
	}
	
	
	// Question 1
	//printf("\nEnter the stock name : ");
	int comp_num;
	scanf("%d",&comp_num);
	printf("\n--------> Question 1");
	per_change(dates,comp_num,last_date-1);
	
	// Question 2
	int day;
	//printf("\nEnter the day on which you wish to sort : ");
	scanf("%d",&day);
	printf("\n--------> Question 2");
	printf("\nsort  stocks <volume-wise, close prices> wise on a day %d\n",day);
	sort_vol(dates,day);
	
	// Question 3 
	int bought_day,sold_day;
	//printf("\nEnter the bought day and sold day respectively : ");
	printf("\n--------> Question 3");
	scanf("\n%d %d",&bought_day,&sold_day);
	profit_loss(dates,bought_day,bought_day);
	
	//Question 4
	int start,end;
	//printf("\nEnter the starting and ending day : ");
	printf("\n--------> Question 4");
	scanf("\n%d %d",&start,&end);
	high_perform(dates , start , end);
	
	//Question 5
	printf("\n--------> Question 5");
	//printf("\nEnter the starting and ending day : ");
	scanf("\n%d %d",&start,&end);
	low_perform(dates , start , end);
	
	//Question 6
	//printf("\nEnter the starting and ending day : ");
	printf("\n--------> Question 6");
	scanf("\n%d %d",&start,&end);
	overall_performance(dates , start , end);
	
	//Question 7(a)
	//printf("\nEnter the day on which you want to calculate average : ");
	int avg_day;
	scanf("\n%d",&avg_day);
	printf("\n--------> Question 7");
	float avg;
	avg=average_value(dates , avg_day);
	printf("\nThe average of all stocks on day %d is %f",avg_day,avg);
	//Question 7(b)
	average(dates,last_date);
}
