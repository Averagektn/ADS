Program Lab3;

{$APPTYPE CONSOLE}

Type
  Fields = Record
    Name,Surname,NameByFather,Telephone: String;
  end;

  Pt = ^Base;
  Base = Record
    Data: Fields;
    Next: Pt;
  end;

  TSort = Function(X: Pt): Boolean;
  TFind = Function (X: Pt; Const Praram: String): Boolean;

Var
  Exit: Boolean;
  Selector,Selector2: Integer;
  Str: String;
  First: Pt;

Function SortByTelephone(X: Pt): Boolean;
begin
  Result := X^.Data.Telephone > X^.Next^.Data.Telephone;
end;

Function SortByName(X: Pt): Boolean;
begin
  Result := X^.Data.Name > X^.Next^.Data.Name;
end;

Function SortBySurname(X: Pt): Boolean;
begin
  Result := X^.Data.Surname > X^.Next^.Data.Surname;
end;

Function SortByNameByFather(X: Pt): Boolean;
begin
  Result := X^.Data.NameByFather > X^.Next^.Data.NameByFather;
end;

Function FoundSurname(X: Pt; Const Param: String): Boolean;
begin
  Result := X^.Data.Surname = Param;
end;

Function FoundTelephone(X: Pt; Const Param: String): Boolean;
begin
  Result := X^.Data.Telephone = Param;
end;

Procedure Sort (Start: Pt; Compare: TSort);
Var
  I, J, Len: Integer;
  X: Pt;
  Temp: Fields;
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
    for J := 1 to Len - I - 1 do
    begin
      if Compare(X) then
      begin
        Temp := X^.Data;
        X^.Data := X^.Next^.Data;
        X^.Next^.Data := Temp;
      end;
      X := X^.Next;
    end;
  end;
end;

Procedure CheckTelephone(Var Param: String);
Var
  I,Check,Error: Integer;
  Flag: Boolean;
begin
  repeat
    Flag := true;
    readln(Param);
    for I := 1 to length(Param) do
    begin
      val(Param[I],Check,Error);
      if Error <> 0 then
        Flag := false;
    end;
    if (not Flag) or (length(Param) <> 7) then
      writeln('Incorrect input');
  until (length(Param) = 7) and (Flag);
end;

Procedure Push (X: Pt);
Var
  Y: Pt;
begin
  while X^.Next <> nil do
    X := X^.Next;
  writeln('Enter telephone number');
  CheckTelephone(X^.Data.Telephone);
  writeln('Enter name');
  readln(X^.Data.Name);
  writeln('Enter surname');
  readln(X^.Data.Surname);
  writeln('Enter name by father');
  readln(X^.Data.NameByFather);
  Y := X;
  new(X);
  Y^.Next := X;
  X^.Next := nil;
end;

Procedure WriteElem(X: Pt);
begin
  writeln('Telephone number: ',X^.Data.Telephone);
  writeln('Name: ',X^.Data.Name);
  writeln('Surname: ',X^.Data.Surname);
  writeln('Name by father: ',X^.Data.NameByFather);
end;

Procedure Print(X: Pt);
begin
  while X^.Next <> nil do
  begin
    WriteElem(X);
    X := X^.Next;
    writeln;
  end;
  writeln;
end;

Procedure Find(X: Pt; Const Param: String; Found: TFind);
Var
  Flag: Boolean;
begin
  Flag := false;
  while X^.Next <> nil do
  begin
    if Found(X,Param) then
    begin
      Flag := true;
      WriteElem(X);
    end;
    X := X^.Next;
  end;
  if not Flag then
    writeln('No matches');
  writeln;
end;

begin
  Exit := false;
  new(First);
  while not Exit do
  begin
    writeln;
    writeln('Press 1 to add a member');
    writeln('Press 2 to show list');
    writeln('Press 3 to find a member by telephone number');
    writeln('Press 4 to find a telephone number by surname');
    writeln('Press 5 to exit');
    readln(Selector);
    writeln;
    case Selector of
      1:
        Push(First);
      2:
        begin
          writeln('Choose sort parameter:');
          writeln('Press 1 to sort by telephone number');
          writeln('Press 2 to sort by name');
          writeln('Press 3 to sort by surname');
          writeln('Press 4 to sort by name by father');
          readln(Selector2);
          case Selector2 of
            1:
              Sort(First,SortByTelephone);
            2:
              Sort(First,SortByName);
            3:
              Sort(First,SortBySurname);
            4:
              Sort(First,SortByNameByFather);
            else
            begin
              writeln('Incorrect input. List was sorted by name');
              Sort(First,SortByName);
            end;
            end;
          Print(First);
        end;
      3:
        begin
          writeln('Enter telephone number');
          readln(Str);
          Find(First,Str,FoundTelephone);
        end;
      4:
        begin
          writeln('Enter surname');
          readln(Str);
          Find(First,Str,FoundSurname);
        end;
      else
        Exit := true;
      end;
  end;
end.
