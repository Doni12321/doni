## Fix Error

Terjadi error pada latihan33_upload.php terjadi karena script itu coba akses ```$_FILES['fupload']``` padahal **Key** ```fupload``` enggak ada di array ```$_FILES```.