cd ..\..
echo Files Changed:
git status -s
echo.
set /p msg=Commit message:
git add -A
git commit -m "%msg%"
git push
PAUSE