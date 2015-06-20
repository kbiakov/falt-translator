program progPas;
var i: Integer;
var f: Real;
begin
i:= 10;
f:= 5.2;
if   i > f then
begin
while  (i >= f)  do
begin
i:= i - f/10;
f:= f + 1;
end;
end;
i:= i + f*10/i;
end.
