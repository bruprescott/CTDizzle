%If viewing this in MATLAB, use the "deploytool" command to create a standalone application.
%The returned executable does not require MATLAB to run, but you will need to install the free MCR runtime.
%This script will plot profiles, time-series, and a table of salinity and temperature data by fathom.
%Plots and converted data are saved automatically by date and time in a script created folder in the C: drive.
%Your data must be in the form of "MM/dd/uuuu,HH:mm:ss,EC,T,P"
%Feel free to modify this code as you see fit.
%Please contact Ian Black (blackia@oregonstate.edu) with any questions, comments, or concerns.

[filename, pathname] = uigetfile({'*.csv';'*.txt'},'Select OpenCTD Data'); %Open a search window.
filepath=fullfile(pathname,filename);   %Holds location of chosen file.
Data=readtable(filepath,'Delimiter',',','Format','%{MM/dd/uuuu}D %{HH:mm:ss}D %f %f %f','HeaderLines',7,'ReadVariableNames',false); 
%Read the file and create a table seperated by the commas. Skip the first 7 lines in case of bad data from EC circuit.

Date=table2array(Data(:,1));  %Create a Date array.
Time=table2array(Data(:,2));  %Create a Time array.
EC=table2array(Data(:,3));    %Create an EC array in uS/cm.
T=table2array(Data(:,4));     %Create a T array in degC.
P=table2array(Data(:,5));     %Create a P array in millibars.

%Combine Date and Time
CnvtDT=@(Date,Time) datetime([Date.Year Date.Month Date.Day Time.Hour Time.Minute Time.Second], 'Format', 'MM.dd.yy HH:mm:ss');
DateTime=CnvtDT(Date,Time);

%Coefficients for Pressure to Depth Conversion (See AN69 by SeaBird Scientific)
Coeff1=-1.82*10^-15;
Coeff2=2.279*10^-10;
Coeff3=2.2512*10^-5;
Coeff4=9.72659;
g=9.806;

%PSS-78 Coefficients (See AN14 by SeaBird Scientific)
A1=2.070*10^-5;
A2=-6.370*10^-10 ;
A3=3.989*10^-15;
B1=3.426*10^-2;
B2=4.464*10^-1;
B3=4.215*10^-1;
B4=-3.107*10^-3;
c0=6.766097*10^-1;
c1=2.00564*10^-2;
c2=1.104259*10^-4;
c3=-6.9698*10^-7;
c4=1.0031*10^-9;
a0=0.0080;
a1=-0.1692;
a2=25.3851;
a3=14.0941;
a4=-7.0261;
a5=2.7081;
b0=0.0005;
b1=-0.0056;
b2=-0.0066;
b3=-0.0375;
b4=0.0636;
b5=-0.0144;
k=0.0162;
CStandard=42.914;

%Salinity Calculations
R=((EC/1000)/CStandard);
RpNumerator=(A1*P/100)+(A2*(P/100).^2)+(A3*(P/100).^3);
RpDenominator=1+(B1.*T)+(B2.*T.^2)+(B3.*R)+(B4.*T.*R);
Rp=1+(RpNumerator./RpDenominator);
rT=c0+(c1.*T)+(c2.*T.^2)+(c3.*T.^3)+(c4.*T.^4);
RT=R./(rT.*Rp);

%Calculating Salinity
S=(a0+(a1*RT.^0.5)+(a2*RT)+(a3*RT.^1.5)+(a4*RT.^2)+(a5*RT.^2.5))+((T-15)/(1+k*(T-15)))*(b0+(b1*RT.^0.5)+(b2*RT)+(b3*RT.^1.5)+(b4*RT.^2)+(b5*RT.^2.5));

%Calculating Depth (meters) from Absolute Pressure
D = (((((Coeff1.*(P/100)+Coeff2).*(P/100)-Coeff3).*(P/100)+Coeff4).*(P/100))/g)-10;

%Combine data into a new array and remove the top fathom of each profile.
ConvertedData=horzcat(D*0.546807,T*1.8+32,S); %Convert meters to fathoms. Convert degC to degF.
ind = ConvertedData(:,1)<1; 
CleanData=removerows(ConvertedData,'ind',ind); %Cleaned up data array.

%Define columns to make plotting a little easier.
Depth=CleanData(:,1);
Temperature=CleanData(:,2);
Salinity=CleanData(:,3);

NAMECNVT=@(Date,Time) datetime([Date.Year Date.Month Date.Day Time.Hour Time.Minute Time.Second], 'Format', 'yyyy-MM-dd_HHmm');
NAME=NAMECNVT(Date,Time);
NEWFILENAME=char(NAME(1,1));

cd C:\
mkdir OpenCTD_Data
cd C:\OpenCTD_Data
mkdir (NEWFILENAME)
cd (NEWFILENAME)

%Create plots of profiles
figure('Name','Profiles','NumberTitle','off');  
subplot(121)  %Temperature Profile
scatter(Temperature,-Depth,'r.')
xlim([min(Temperature)-3 min(Temperature)+3]) %Set x-axis limits to +/- 2 of minimum temperature value.
xlabel('Temperature (degF)')
ylabel('Depth (fathoms)')
title('Temperature Profile')

subplot(122)  %Salinity Profile
scatter(Salinity,-Depth,'b.')
xlim([max(Salinity)-5 max(Salinity)+5]) %Set x-axis limits to +/- 5 of maximum salinity value.
xlabel('Salinity (PSU)')
ylabel('Depth (fathoms)')
title('Salinity Profile')

profname=char(strcat({NEWFILENAME},{'_Profiles'}));
saveas(gcf,profname,'jpeg')

%Create time-series plots.
figure('Name','Time-Series','NumberTitle','off'); 
subplot(311)    %Temperature Time-Series
plot(DateTime,T*1.8+32,'r')
xlabel('Date and Time')
ylabel('Temperature (degF)')
title('Temperature Time-Series')

subplot(312)
plot(DateTime,S,'b')    %Salinity Time-Series
xlabel('Date and Time')
ylabel('Salinity (PSU)')
title('Salinity Time-Series')

subplot(313)
plot(DateTime,-D*0.546807,'k')   %Depth Time-Series
xlabel('Date and Time')
ylabel('Depth (fathoms)')
title('Depth Time-Series')

seriesname=char(strcat({NEWFILENAME},{'_TimeSeries'}));
saveas(gcf,seriesname,'jpeg')


%Display table of converted data.
f=figure('Name','Table','NumberTitle','off');
t=uitable(f);
t.Data= ConvertedData;
t.ColumnName={'Depth (Fathoms)','Temperature (F)','Salinity'};
t.ColumnEditable=true;

name=char(strcat({NEWFILENAME},{'_Processed'},'.csv'));
csvwrite(name,ConvertedData);

