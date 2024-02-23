int Josephus(int size)
{
	int arr[size] = (int*) malloc(sizeof(int) * 100);
	int i = 0;
	while (i < size -1)
	{
		arr[i] = i + 1;
	}
	arr[i] = 0;
	while (arr[i] != arr[arr[i]])
	{
		i = i % size;
		arr[i] = arr[arr[i]];
		i++;
	}
	return arr[i];
		
	
}
