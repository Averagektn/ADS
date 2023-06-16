Program Lab4;

{$APPTYPE CONSOLE}

Type
  Elem = Record
    Degree,Coef: Integer;
  end;

  Pt = ^Base;
  Base = Record
    Data: Elem;
    Next: Pt;
  end;

  TSort = Function(X: Pt): Boolean;
  TFind = Function (X: Pt; Const Praram: String): Boolean;

Var
  Exit: Boolean;
  Selector,Point: Integer;
  FirstP,FirstQ,FirstR: Pt;

Procedure Make (Var X: Pt);
Var
  I,Len,D: Integer;
  Y,Z: Pt;
begin
  Y := X;
  X^.Data.Coef := 0;
  X^.Data.Degree := 0;
  writeln('Enter the highest degree');
  readln(Len);
  for I := Len downto 0 do
  begin
    writeln('Enter the coefficent before the ',I,' degree');
    readln(D);
    if D <> 0 then
    begin
      X^.Data.Coef := D;
      X^.Data.Degree := I;
      Z := X;
      if I > 0 then
      begin
        new(X^.Next);
        X := X^.Next;
      end;
    end;
  end;
  if D = 0 then
    Z^.Next := nil;
  X^.Next := nil;
  X := Y;
end;

Procedure Print(X: Pt);
begin
  while X^.Next <> nil do
  begin
    write(X^.Data.Coef,'x^',X^.Data.Degree,' + ');
    X := X^.Next;
  end;
  if X^.Data.Degree = 0 then
    write(X^.Data.Coef)
  else
    write(X^.Data.Coef,'x^',X^.Data.Degree);
end;

Procedure Equality(P,Q: Pt);
Var
  Flag: Boolean;
  PC,QC: Pt;
begin
  PC := P;
  QC := Q;
  Flag := true;
  while (P^.Next <> nil) and (Q^.Next <> nil) do
  begin
    if (P^.Data.Degree <> Q^.Data.Degree) or (P^.Data.Coef <> Q^.Data.Coef) then
      Flag := false;
    P := P^.Next;
    Q := Q^.Next;
  end;
  if Flag then
  begin
    Print(PC);
    write(' = ');
    Print(QC);
  end
  else
  begin
    Print(PC);
    write(' <> ');
    Print(QC);
  end;
end;

Procedure Meaning(P: Pt; Const X: Integer);
Var
  Res,Tmp,I: Integer;
  PC: Pt;
begin
  PC := P;
  Res := 0;
  while P^.Next <> nil do
  begin
    Tmp := P^.Data.Coef;
    for I := 1 to P^.Data.Degree do
      Tmp := Tmp * X;
    Res := Res + Tmp;
    P := P^.Next;
  end;
  Res := Res + P^.Data.Coef;
  Print(PC);
  writeln(' = ',Res);
end;

Procedure Add(P,Q,R: Pt);
Var
  PC,QC,RC,C: Pt;
begin
  PC := P;
  QC := Q;
  RC := R;
  while (P <> nil) and (Q <> nil) do
  begin
    if P^.Data.Degree >= Q^.Data.Degree then
    begin
      if P^.Data.Degree = Q^.Data.Degree then
      begin
        R^.Data.Degree := P^.Data.Degree;
        R^.Data.Coef := P^.Data.Coef + Q^.Data.Coef;
        Q := Q^.Next;
      end
      else
        R^.Data := P^.Data;
      P := P^.Next;
    end
    else
    begin
      R^.Data := Q^.Data;
      Q := Q^.Next;
    end;
    C := R;
    new(R^.Next);
    R := R^.Next;
  end;

  while P <> nil do
  begin
    R^.Data := P^.Data;
    P := P^.Next;
    C := R;
    new(R^.Next);
    R := R^.Next;
  end;

  while Q <> nil do
  begin
    R^.Data := Q^.Data;
    Q := Q^.Next;
    C := R;
    new(R^.Next);
    R := R^.Next;
  end;

  C^.Next := nil;

  Print(PC);
  write(' + ');
  Print(QC);
  write(' = ');
  Print(RC);
end;

begin
  Exit := false;
  new(FirstP);
  new(FirstQ);
  new(FirstR);
  writeln('Enter the first polynomial');
  Make(FirstP);
  writeln('Enter the second polynomial');
  Make(FirstQ);
  writeln('The first polynomial');
  Print(FirstP);
  writeln;
  writeln('The second polynomial');
  Print(FirstQ);
  writeln;

  while not Exit do
  begin
    writeln('Choose operation');
    writeln('Press 1 to check if polynoms are equal');
    writeln('Press 2 to find the meaning of the polynoms in point');
    writeln('Press 3 to add polynoms');
    writeln('Press 4 to quit');
    readln(Selector);
    writeln;
    Case Selector of
    1:
      Equality(FirstP,FirstQ);
    2:
    begin
      writeln('Enter the point');
      readln(Point);
      writeln;
      writeln('First polynom: ');
      Meaning(FirstP,Point);
      writeln;
      writeln('Second polynom: ');
      Meaning(FirstQ,Point);
    end;
    3:
      Add(FirstP,FirstQ,FirstR);
    else
      Exit := true;
    end;
  end;
end.

