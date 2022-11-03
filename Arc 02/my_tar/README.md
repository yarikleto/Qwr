#### Arguments' validation

- [x] `my_tar`
```text
tar: Must specify one of -c, -r, -t, -u, -x
```
- [x] `my_tar -f`
```text
tar: Option -f requires an argument
```
- [x] `my_tar -f kek.tar`
```text
tar: Must specify one of -c, -r, -t, -u, -x
```
- [x] `my_tar -c`
```text
tar: no files or directories specified
```
- [x] `my_tar -cx`
```text
tar: Can't specify both -x and -c
```
- [ ] `my_tar -xc`
```text
tar: Can't specify both -c and -x
```
- [x] `my_tar -cu`

```text
Can't specify both -u and -c
```
- [x] `my_tar -cr`

```text
tar: Can't specify both -r and -c
```
- [ ] `my_tar test -c -f kek.tar`

```text
Usage:
  List:    tar -tf <archive-filename>
  Extract: tar -xf <archive-filename>
  Create:  tar -cf <archive-filename> [filenames...]
```
- [x] `my_tar -fc kek.tar`

```text
tar: Must specify one of -c, -r, -t, -u, -x
```
- [x] `my_tar -cf kek.tar`

```text
tar: no files or directories specified
```
- [x] `my_tar -cf kek.tar my_tar` -> **VALID**
