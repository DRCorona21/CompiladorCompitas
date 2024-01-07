void ImprimeTabla()//Funcion de depuracion
{
	auxTabla = PTabla;
	cout<<"\t\t\t\tTABLA DE SIMBOLOS"<<endl;
	cout<<"-----------------------------------------------------------------------------------------"<<endl;
	cout<<"LEXEMA\t\tTIPO TOKEN\tTIPO DE DATO\tREGLA\t\tINDICE"<<endl;
	cout<<"-----------------------------------------------------------------------------------------"<<endl;
	while(auxTabla != NULL)
	{
		cout<<auxTabla->lexema<<"\t\t"<<auxTabla->tipoToken<<"\t\t"<<auxTabla->tipDat<<"\t\t"<<auxTabla->regla<<"\t\t"<<auxTabla->ind<<endl;
		auxTabla = auxTabla->liga;
	}
	cout<<"-----------------------------------------------------------------------------------------"<<endl;
}