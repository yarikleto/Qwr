clean () {
  rm -f ./tar.out ./my_tar.out ./diff.out
}

tar -f &> tar.out
../my_tar -f &> my_tar.out
diff tar.out my_tar.out > diff.out

DIFF_FILESIZE=$(ls -lh diff.out | awk '{print $5}')

if [ DIFF_FILESIZE != "0B" ]; then
  echo "'my_tar -f' has an error:"
  echo "------DIFF-----"
  cat ./diff.out
  echo "---------------"
  clean
  exit 1
fi

clean
