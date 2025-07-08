<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Sistem Komentar Blog Mini</title>
  <link rel="stylesheet" href="save.php">
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 40px;
      background: #f9f9f9;
    }
    .form-container {
      background: #fff;
      padding: 20px;
      width: 400px;
      border: 1px solid #ccc;
      border-radius: 8px;
      margin-bottom: 20px;
    }
    .form-container h2 {
      margin-top: 0;
    }
    input[type="text"], textarea {
      width: 100%;
      padding: 8px;
      margin-top: 5px;
      margin-bottom: 15px;
      border: 1px solid #ccc;
      border-radius: 4px;
    }
    button {
      background-color: #28a745;
      color: white;
      border: none;
      padding: 10px 15px;
      border-radius: 4px;
      cursor: pointer;
    }
    button:hover {
      background-color: #218838;
    }
    .comment {
      background: #fff;
      border-left: 4px solid #28a745;
      padding: 10px;
      margin-bottom: 10px;
    }
    .comment strong {
      display: block;
      margin-bottom: 5px;
    }
  </style>
</head>
<body>
  <div class="form-container">
    <h2>Form Komentar</h2>
    <form id="commentForm" method="POST" action="save.php" onsubmit="return validateForm()">
      <label>Nama:</label>
      <input type="text" name="nama" id="nama">
      <label>Komentar:</label>
      <textarea name="komentar" id="komentar" rows="4"></textarea>
      <button type="submit">Kirim Komentar</button>
    </form>
  </div>

  <h3>Komentar Sebelumnya:</h3>
  <?php
    $filename = 'komentar.txt';
    if (file_exists($filename)) {
      $data = file($filename, FILE_IGNORE_NEW_LINES);
      foreach ($data as $line) {
        list($nama, $komentar) = explode('|', $line, 2);
        echo "<div class='comment'><strong>".htmlspecialchars($nama)."</strong>".htmlspecialchars($komentar)."</div>";
      }
    } else {
      echo "<p>Belum ada komentar.</p>";
    }
  ?>
  
  <script>
    function validateForm() {
      const nama = document.getElementById("nama").value.trim();
      const komentar = document.getElementById("komentar").value.trim();
      if (nama === "" || komentar === "") {
        alert("Nama dan komentar tidak boleh kosong!");
        return false;
      }
      return true;
    }
  </script>
</body>
</html>
