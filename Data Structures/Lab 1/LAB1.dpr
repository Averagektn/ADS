Program LAB1;

{$APPTYPE CONSOLE}

Type
  Pt = ^Elem;
  Elem = Record
    Data: String;
    Next, Prev: Pt;
  end;

  Pt1 = ^Elem1;
  Elem1 = Record
    Data: String;
    Next: Pt1;
  end;

Var
  First: Pt;
  Second: Pt1;

Procedure Make (Var X: Pt);
Var
  I, Check, Error, Len: Integer;
  Y: Pt;
begin
  new(X);
  write('Enter the number of telephone numbers ');
  readln(Len);
  X^.Prev := nil;
  for I := 0 to Len - 1 do
  begin
    Y := X;
    repeat
      write('Enter the telephone number ');
      readln(X^.Data);
      val(X^.Data,Check,Error);
      if ((length(X^.Data) <> 7) and (length(X^.Data) <> 3)) or (Error <> 0) then
        writeln('Incorrect input');
    until ((length(X^.Data) = 7) or (length(X^.Data) = 3)) and (Error = 0);
    if I < Len-1 then
    begin
      new(X);
      Y^.Next := X;
      X^.Prev := Y;
    end;
  end;
  Y^.Next := nil;
end;

Procedure Print (X: Pt);
begin
  while X <> nil do
  begin
    writeln(X^.Data);
    X := X^.Prev;
  end;
end;

Procedure Telephone_7 (Y: Pt1; X: Pt);
begin
  while X <> nil do
  begin
    if length(X^.Data) = 7 then
    begin
      New(Y^.Next);
      Y := Y^.Next;
      Y^.Data := X^.Data;
    end;
    X := X^.Prev;
  end;
  Y^.Next := nil;
end;

Procedure Sort (Start: Pt1);
Var
  I, J, Len: Integer;
  X: Pt1;
  Temp: String;
begin
  X := Start;
  Len := 0;
  while X <> nil do
  begin
    Inc(Len);
    X := X^.Next;
  end;
  for I := 1 to Len do
  begin
    X := Start;
    for J := 1 to Len - I do
    begin
      if X^.Data > X^.Next^.Data then
      begin
        Temp := X^.Data;
        X^.Data := X^.Next^.Data;
        X^.Next^.Data := Temp;
      end;
      X := X^.Next;
    end;
  end;
end;

Procedure Print_1 (Y: Pt1);
begin
  while Y <> nil do
  begin
    writeln(Y^.Data);
    Y := Y^.Next;
  end;
end;

Begin
  Make(First);
  writeln;
  writeln('Two-directional list:');
  Print(First);
  New(Second);
  Telephone_7(Second,First);
  Sort(Second);
  writeln;
  write('Sorted one-directional list:');
  Print_1(Second);
  readln;
end.
