%Running this script, either in MATLAB or as deploytool will process RAWCTD
%files in the form of Date,Time,EC,T,P,Depth,Sal,Density. The script
%ignores the Depth, Sal, and Density values derived by the MKRZero and
%calculates depth and salinity separately.

%Three windows will pop up. 1)Downcast profiles of temperature and
%salinity, 2)Time-series of temperature and salinity, 3)Table of converted
%values.

%This data will also be saved to the C: drive in a folder called
%"OpenCTD_Data" with the date and time as the filename. This version has
%not been tested on Apple hardware, so the directory structure should be
%changed to reflect Apple structuring if using Apple hardware.

%The EC EZO defaults to 25 degrees for temperature compensation. This sketch utilizes a linear EC-temp relationship to derive a
%temperature compensated EC value. This is based on the assumption that the
%temperature compensation factor is 0.02. This is an adequate assumption
%in 0-30 degC waters per Hayashi 2003.

[filename, pathname] = uigetfile({'*.csv';'*.txt'},'Select OpenCTD Data'); %Open a search window.
filepath=fullfile(pathname,filename);   %Holds location of chosen file.
Data=readtable(filepath,'Delimiter',',','Format','%{MM/dd/uuuu}D %{HH:mm:ss}D %f %f %f %f %f %f','HeaderLines',0,'ReadVariableNames',false); %Read the csv and create a data array with eight columns.

Date=table2array(Data(:,1));  %Create a Date array.
Time=table2array(Data(:,2));  %Create a Time array.
CnvtDT=@(Date,Time) datetime([Date.Year Date.Month Date.Day Time.Hour Time.Minute Time.Second], 'Format', 'MM.dd.yy HH:mm:ss');
DateTime=CnvtDT(Date,Time);   %Create a DateTime array. 
EC=table2array(Data(:,3));    %Create an EC array in uS/cm.
T=table2array(Data(:,4));     %Create a T array in degC.
P=table2array(Data(:,5));     %Create a P array in millibars.

for L=length(DateTime)  %This will smooth data based on the amount collected (assuming 1Hz sampling rate).
    if L <= 600     %If there is less than ten minutes of data...
        MovValue = 10;      %k=10
    elseif L > 600 && L <= 7200  %If there is less than two hours but more than 10 minutes of data...
        MovValue = 30;      %k=30
    else
        MovValue = 300;     %k-300
    end %Determines the k value for the moving mean based on number of samples taken.
end

%PSS-78 Coefficients (See AN14 by SeaBird Scientific)
A1=2.070*10^-5; A2=-6.370*10^-10; A3=3.989*10^-15;
B1=3.426*10^-2; B2=4.464*10^-1; B3=4.215*10^-1; B4=-3.107*10^-3;
c0=6.766097*10^-1; c1=2.00564*10^-2; c2=1.104259*10^-4; c3=-6.9698*10^-7; c4=1.0031*10^-9;
a0=0.0080; a1=-0.1692; a2=25.3851; a3=14.0941; a4=-7.0261; a5=2.7081;
b0=0.0005; b1=-0.0056; b2=-0.0066; b3=-0.0375; b4=0.0636; b5=-0.0144;
k=0.0162; CStandard=42.914;
CompEC = EC.*(1+0.02.*(T-25));

latprompt = {'Enter the deployed latitude in decimal degrees.'}; %Create a prompt window asking for latitude.
dlg_title= 'Latitude';
num_lines = 1;
defaultans = {'45.00'}; %Display the default latitude as 45.00 deg.
latitude = cell2mat(inputdlg(latprompt,dlg_title,num_lines,defaultans)); %Store the latitude value.

AtmP=P(1,1);   %Determine atmospheric pressure from the first pressure value.
p=(P-AtmP)./100;  %Calculate gauge pressure in decibars.
x=sin((latitude(1,1))/57.29578);
y=x.*x;
gr = 9.780318 .* (1.0 + (5.2788e-3 + 2.36e-5 .* y) .* y) + 1.092e-6 .* p;
D_meters = ((((-1.82e-15 .* p + 2.279e-10) .* p - 2.2512e-5) .* p + 9.72659) .* p)./gr;


%Salinity Calculations (See AN14 by Seabird Scientific)
R=((CompEC/1000)/CStandard);
RpNumerator=(A1*p)+(A2*(p).^2)+(A3*(p).^3);
RpDenominator=1+(B1.*T)+(B2.*T.^2)+(B3.*R)+(B4.*T.*R);
Rp=1+(RpNumerator./RpDenominator);
rT=c0+(c1.*T)+(c2.*T.^2)+(c3.*T.^3)+(c4.*T.^4);
RT=R./(rT.*Rp);
S=(a0+(a1.*RT.^0.5)+(a2.*RT)+(a3.*RT.^1.5)+(a4.*RT.^2)+(a5.*RT.^2.5))+((T-15)./(1+k.*(T-15))).*(b0+(b1.*RT.^0.5)+(b2.*RT)+(b3.*RT.^1.5)+(b4.*RT.^2)+(b5.*RT.^2.5));  %Gives salinity in PSU.

Filter1=horzcat(D_meters,T,S);
ind = Filter1(:,1)<1;
Filter2=removerows(Filter1,'ind',ind); %Cleaned up data array.
[M,I]=max(Filter2(:,3));
Downcast = horzcat(Filter2(1:I,1),Filter2(1:I,2),Filter2(1:I,3)); %D,T,S
MovS = movmean(Downcast(:,3),MovValue,'omitnan');  %Calculate the moving mean for salinity.
MovT = movmean(Downcast(:,2),MovValue,'omitnan');  %Calculate the moving mean for temperature.
 
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
scatter(MovT,Downcast(:,1),'r.')
hold on
xlabel('Temperature (degC)')
ylabel('Depth (meters)')
title('Temperature Profile')
set(gca,'Ydir','reverse')
hold off

subplot(122)  %Salinity Profile
hold on
scatter(MovS,Downcast(:,1),'b.')
xlabel('Salinity (PSU)')
ylabel('Depth (meters)')
title('Salinity Profile')
set(gca,'Ydir','reverse')
hold off

profname=char(strcat({NEWFILENAME},{'_Profiles'}));
saveas(gcf,profname,'jpeg')

%Create time-series plots.
figure('Name','Time-Series','NumberTitle','off'); 
subplot(311)    %Temperature Time-Series
hold on
plot(DateTime,T,'r','LineWidth',2)
xlabel('Date and Time')
ylabel('Temperature (degC)')
title('Temperature Time-Series')
hold off

subplot(312)
hold on
plot(DateTime,S,'b','LineWidth',2)    %Salinity Time-Series
xlabel('Date and Time')
ylabel('Salinity (PSU)')
title('Salinity Time-Series')
hold off

subplot(313)
hold on
plot(DateTime,D_meters,'k','LineWidth',2)   %Depth Time-Series
xlabel('Date and Time')
ylabel('Depth (meters)')
title('Depth Time-Series')
set(gca,'Ydir','reverse')
hold off

seriesname=char(strcat({NEWFILENAME},{'_TimeSeries'}));
saveas(gcf,seriesname,'jpeg')


%Display table of downcast data.
f=figure('Name','Table','NumberTitle','off');
t=uitable(f);
t.Data= Downcast;
t.ColumnName={'Depth (m)','Temp (degC)','Salinity (PSU)'};
t.ColumnEditable=false;
set(t,'Units','inches','Position',[0 0 4 4],'ColumnWidth',{105})

name=char(strcat({NEWFILENAME},{'_Processed'},'.csv'));
csvwrite(name,Downcast);


