#include "Header.h"

bool Grade_Validation(uint8_t* grade)
{
	//check that grade is between 0 and 100
	for (int i = 0; i < 3; i++)
	{
		if (grade[i] < 0 || grade[i]>100)
		{
			printf("Invalid grade\n");
			return 0; //Invalid Grade
		}
		else
		{

		}
	}
	return 1; //Valid Grade
}
bool Year_Validation(uint8_t* year)
{
	//check that year is between 1 and 12
	if (*year < 1 || *year>12)
	{
		printf("Invalid year\n");
		return 0; //Invalid year
	}
	else
	{
		return 1; //Valid year
	}
}
bool ID_Validation(uint8_t* id)
{
	//check that ID is between 1 and 10
	if (*id < 1 ||  *id > 10)
	{
		printf("Invalid Id\n");
		return 0; //ID is invalid
	}
	else
	{
		return 1; //ID is Valid
	}
}
uint8_t SDB_GetUsedSize()
{
	uint8_t counter = 0;
	for (int i = 0; i < Max; i++)
	{
		if (Database[i].ID != 0) //if ID=0 it means this entry is empty
		{
			counter++;
		}
		else
		{
		}
	}
	return counter; //counter of filled elements
}
bool SDB_IsFull()
{
	uint8_t counter = SDB_GetUsedSize();
	if(counter==Max)// Database is full
    {
        return 1;
    }
    else
    {
        return 0; //Not Full
    }
}

bool SDB_IsIdExist(uint8_t id)
{
	//first check if this ID already exists
	for (int i = 0; i < Max; i++)
	{
		if (Database[i].ID == id)
		{
			return 1; //ID already exists
		}
		else
		{

		}
	}
	return 0; //ID does not exist

}
bool SDB_AddEntry(uint8_t id, uint8_t year, uint8_t* subjects, uint8_t* grades)
{
    if(SDB_IsIdExist(id)==1) printf("ID Already Exist!\n");
	if (SDB_IsIdExist(id) == 1 || Grade_Validation(grades) == 0 || Year_Validation(&year)==0 || ID_Validation(&id)==0) // ID already exists/Invalid or grade/year invalid
	{
		return 0; //Unsuccessful entry
	}
	else
	{
		Database[id - 1].ID = id;
		Database[id - 1].Year = year;
		for (int i = 0; i < 3; i++)
		{
			Database[id - 1].Subjects[i].ID = *subjects;
			Database[id - 1].Subjects[i].Grade = *grades;
			subjects++;
			grades++;
		}

	}
	return 1; //Successful entry
}
void SDB_DeleteEntry(uint8_t id)
{
	if (SDB_IsIdExist(id) == 1) // ID Exists
	{
		Student Empty = { 0 }; // Declare an empty Student Struct
		Database[id - 1] = Empty; //Delete the specified entry
		printf("Entry Deleted Successfully\n");
	}
	else
	{
		printf("Entry Does not Exist, Try Again!\n");
	}
}
bool SDB_ReadEntry(uint8_t id, uint8_t* year, uint8_t* subjects, uint8_t* grades)
{
	if (SDB_IsIdExist(id) == 1) //ID exists
	{
		*year = Database[id - 1].Year;
		for (int i = 0; i < 3; i++)
		{
			*subjects = Database[id - 1].Subjects[i].ID;
			*grades = Database[id - 1].Subjects[i].Grade;
			subjects++;
			grades++;
		}
		return 1;
	}
	else
	{
		return 0; //Entry does not exist
	}
}
void SDB_GetIdList(uint8_t* count, uint8_t* list)
{
	*count = SDB_GetUsedSize();
	char j = 0;
	for (int i = 0; i < Max; i++)
	{
		if (Database[i].ID != 0)
		{
			list[j] = Database[i].ID;
			j++;
		}
		else
		{

		}
	}

}
int main()
{
    uint8_t count = 0,x=0,id = 0, year = 0;
	uint8_t choice = 0;
	printf("Welcome to Student Database\n");
	while (choice != 8)
	{
	    uint8_t subjects[3] = { 0 },grades[3] = { 0 };
		printf("Choose From The Following List a Function to Carry!\n1.Check if the Database is Full.\n2.Get Number of Entries in The Database.\n3.Add an Entry\n4.Delete an Entry.\n5.Read an Entry.\n6.Get List of Students' IDs.\n7.Check If an ID Exists\n8.Exit.\n");
		printf("Enter Your No. of Choice: ");
		scanf("%d", &x);
		choice=x;
		uint8_t* list = (uint8_t*)malloc(count * sizeof(uint8_t));
		bool check;
		switch (choice)
		{
		case 1:
			if (SDB_IsFull() == 1)
			{
				printf("Database is FULL!\n\n\n");
			}
			else
			{
				printf("Database is not FULL!\n\n\n");
			}
			break;
		case 2:
			printf("Number of Entries in The Database= %d\n\n\n", SDB_GetUsedSize());
			break;
		case 3:
			printf("Enter ID: ");
			scanf("%d", &x);
			id=x;
			printf("Enter Year: ");
			scanf("%d", &x);
			year=x;
			for (int i = 0; i < 3; i++)
			{
				printf("Enter Subject %d ID: ", i + 1);
				scanf("%d", &x);
				subjects[i]=x;
				printf("Enter Subject %d Grade: ", i + 1);
				scanf("%d",&x);
				grades[i]=x;
			}
			check = SDB_AddEntry(id, year, &subjects, &grades);
			if (check == 1) printf("Successful Entry!\n\n\n");
			else printf("Unsuccessful Entry, Try Again!\n\n\n");
			break;
		case 4:
			printf("Enter ID of Entry To Be Deleted: ");
			scanf("%d", &x);
			id=x;
			SDB_DeleteEntry(id);
			printf("\n\n\n");
			break;
		case 5:
			printf("Enter ID of Entry You Want To Read: ");
			scanf("%d", &x);
			id=x;
			check = SDB_ReadEntry(id, &year, &subjects, &grades);
			if (check == 1)
			{
				printf("Student's ID: %d\nStudent's Year: %d\n", id, year);
				for (int i = 0; i < 3; i++)
				{
					printf("Course_%d ID: %d\nCourse_%d Grade: %d\n", i, subjects[i], i, grades[i]);
				}
			}
			else
			{
				printf("This Entry Does not Exist, Try Again!\n");
			}
			printf("\n\n");
			break;
		case 6:
			SDB_GetIdList(&count, list);
			printf("There are %d Entries in This Database\nIDs of Entries Available are: \n", count);
			for (int i = 0; i < count; i++)
			{
				printf("%d\n", (int)list[i]);
			}
			printf("\n\n");
			break;
		case 7:
			printf("Enter ID You Want To Look For: ");
			scanf("%d", &x);
			id=x;
			check = SDB_IsIdExist(id);
			if (check == 1)
			{
				printf("ID Exists!\n\n\n");
			}
			else printf("ID Does Not Exist!\n\n\n");
			break;
		default:
			break;
		}
	}
	return 0;
}
