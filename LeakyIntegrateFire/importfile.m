function readlog(fileToRead1)
%IMPORTFILE(FILETOREAD1)
%  Imports data from the specified file
%  FILETOREAD1:  file to read

%  Auto-generated by MATLAB on 13-Feb-2009 16:01:09

% Import the file
newData1 = importfile(fileToRead1);

% Create new variables in the base workspace from those fields.
vars = fieldnames(newData1);
for i = 1:length(vars)
    assignin('base', vars{i}, newData1.(vars{i}));
end
time=newData1.data(:,1);
u1=newData1.data(:,2);
plot(time,u1);