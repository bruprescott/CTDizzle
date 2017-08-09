%If viewing this in MATLAB, use the "deploytool" command to create a standalone application.
%The executable does not require MATLAB to run, but you will need to install the free MCR runtime.
%This script will plot profiles and time-series of your raw OpenCTD data, as well as create a new csv of the converted data.
%It saves all of this to a created OpenCTD_Data directory and labels everything by yearmonthdate_time.
%Your data must be in the form of "MM/dd/uuuu,HH:mm:ss,EC,T,P"
%Feel free to modify this code as you see fit.
%Please contact Ian Black (blackia@oregonstate.edu) with any questions, comments, or concerns.

% ISSUES
% 1. Does not consider the latitudinal variation in gravity. If desired, look at AppNote 69 for information on how to include that.
% 2. This currently assumes that the very first pressure sample taken (after the device is turned on) is representative of the local atmospheric pressure.

[filename, pathname] = uigetfile({'*.csv';'*.txt'},'Select OpenCTD Data'); %Open a search window.
filepath=fullfile(pathname,filename);   %Holds location of chosen file.
Data=readtable(filepath,'Delimiter',',','Format','%{MM/dd/uuuu}D %{HH:mm:ss}D %f %f %f','HeaderLines',0,'ReadVariableNames',false); %Read the csv and create a data array.

Date=table2array(Data(5:end,1));  %Create a Date array.
Time=table2array(Data(5:end,2));  %Create a Time array.
CnvtDT=@(Date,Time) datetime([Date.Year Date.Month Date.Day Time.Hour Time.Minute Time.Second], 'Format', 'MM.dd.yy HH:mm:ss');
DateTime=CnvtDT(Date,Time);       %Create a DateTime array.
EC=table2array(Data(5:end,3));    %Create an EC array in uS/cm.
T=table2array(Data(5:end,4));     %Create a T array in degC.
P=table2array(Data(5:end,5));     %Create a P array in millibars.

%Coefficients for Pressure to Depth Conversion (See AN69 by SeaBird Scientific)
Coeff1=-1.82*10^-15; Coeff2=2.279*10^-10; Coeff3=2.2512*10^-5; Coeff4=9.72659; g=9.806;

%PSS-78 Coefficients (See AN14 by SeaBird Scientific)
A1=2.070*10^-5; A2=-6.370*10^-10; A3=3.989*10^-15;
B1=3.426*10^-2; B2=4.464*10^-1; B3=4.215*10^-1; B4=-3.107*10^-3;
c0=6.766097*10^-1; c1=2.00564*10^-2; c2=1.104259*10^-4; c3=-6.9698*10^-7; c4=1.0031*10^-9;
a0=0.0080; a1=-0.1692; a2=25.3851; a3=14.0941; a4=-7.0261; a5=2.7081;
b0=0.0005; b1=-0.0056; b2=-0.0066; b3=-0.0375; b4=0.0636; b5=-0.0144;
k=0.0162; CStandard=42.914;

%Calculating Depth (meters) from Absolute Pressure (See AN69 by SeaBird Scientific)
AtmP = table2array(Data(1,5));    %Assuming first pressure reading is out of water and representative of atmospheric pressure.
GaugeP = (P - AtmP)/100;  %Subtract atmospheric pressure from the read absolute pressure to get gauge pressure in decibars.
D = ((((Coeff1.*GaugeP+Coeff2).*GaugeP-Coeff3).*GaugeP+Coeff4).*GaugeP)/g; %Gives depth in meters as a function of gauge pressure and gravity.

%Salinity Calculations (See AN14 by Seabird Scientific)
R=((EC/1000)/CStandard);
RpNumerator=(A1*GaugeP)+(A2*(GaugeP).^2)+(A3*(GaugeP).^3);
RpDenominator=1+(B1.*T)+(B2.*T.^2)+(B3.*R)+(B4.*T.*R);
Rp=1+(RpNumerator./RpDenominator);
rT=c0+(c1.*T)+(c2.*T.^2)+(c3.*T.^3)+(c4.*T.^4);
RT=R./(rT.*Rp);

%Calculating Salinity
S=(a0+(a1.*RT.^0.5)+(a2.*RT)+(a3.*RT.^1.5)+(a4.*RT.^2)+(a5.*RT.^2.5))+((T-15)./(1+k.*(T-15))).*(b0+(b1.*RT.^0.5)+(b2.*RT)+(b3.*RT.^1.5)+(b4.*RT.^2)+(b5.*RT.^2.5));  %Gives salinity in PSU.

%Combine data into a new array and remove the top 0.5m of each profile.
ConvertedData=horzcat(D,T,S); 
ind = ConvertedData(:,1)<0.5; 
CleanData=removerows(ConvertedData,'ind',ind); %Cleaned up data array.

%Define columns to make plotting a little easier.
Depth=CleanData(:,1);
Temperature=CleanData(:,2);
Salinity=CleanData(:,3);

NAMECNVT=@(Date,Time) datetime([Date.Year Date.Month Date.Day Time.Hour Time.Minute Time.Second], 'Format', 'yyyy-MM-dd_HHmm');
NAME=NAMECNVT(Date,Time);
NEWFILENAME=char(NAME(1,1));  %Name to be used by created folders and files. 

cd C:\  %Assuming you are using windows. Navigate to the C: drive.
mkdir OpenCTD_Data  %Make a folder labeled "OpenCTD_Data". Continues if the folder is already there.
cd C:\OpenCTD_Data  %Change your directory to the folder you made above.
mkdir (NEWFILENAME) %Make a new folder labeled "yyyy-MM-dd_HHmm". The date and time values are from the first line of the Date and Time arrays.    
cd (NEWFILENAME)    %Change your directory to the folder you made above.

figure('Name','Profiles','NumberTitle','off');  %Create a window displaying temperature and salinity profiles.
subplot(121)  %Temperature Profile
scatter(Temperature,-Depth,'r.')
xlim([mean(Temperature)-3 mean(Temperature)+3]) %Set x-axis limits to +/- 2 of mean temperature value.
xlabel('Temperature (degC)')
ylabel('Depth (meters)')
title('Temperature Profile')

subplot(122)  %Salinity Profile
scatter(Salinity,-Depth,'b.')
xlim([mean(Salinity)-2 mean(Salinity)+2]) %Set x-axis limits to +/- 3 of mean salinity value.
xlabel('Salinity (PSU)')
ylabel('Depth (meters)')
title('Salinity Profile')

profname=char(strcat({NEWFILENAME},{'_Profiles'})); 
saveas(gcf,profname,'jpeg')  %Save the profiles figure as a jpeg.

%Create time-series plots.
figure('Name','Time-Series','NumberTitle','off'); %Create a window displaying the time-series pots.
subplot(311)    %Temperature Time-series
plot(DateTime,T,'r')
xlabel('Date and Time')
ylabel('Temperature (degC)')
ylim([mean(T)-3 mean(T)+3])
title('Temperature Time-Series')

subplot(312)
plot(DateTime,S,'b')    %Salinity Time-Series
xlabel('Date and Time')
ylabel('Salinity (PSU)')
ylim([mean(S)-2 mean(S)+2])
title('Salinity Time-Series')

subplot(313)
plot(DateTime,-D,'k')   %Depth Time-Series
xlabel('Date and Time')
ylabel('Depth (m)')
title('Depth Time-Series')

seriesname=char(strcat({NEWFILENAME},{'_TimeSeries'}));
saveas(gcf,seriesname,'jpeg')      %Save the time-series as a jpeg.

%Display table of converted data.
f=figure('Name','Table','NumberTitle','off');
t=uitable(f);
t.Data= ConvertedData;
t.ColumnName={'Depth (Meters)','Temperature (C)','Salinity (PSU)'};
t.ColumnEditable=true;

name=char(strcat({NEWFILENAME},{'_Processed'},'.csv'));
csvwrite(name,ConvertedData);
