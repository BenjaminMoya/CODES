package com.example.demo.controllers;

import com.example.demo.entities.fileEntity;
import com.example.demo.servicies.fileService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import static org.springframework.http.ResponseEntity.ok;

@RestController
@RequestMapping("/api/file")
@CrossOrigin("*")
public class fileController {

    @Autowired
    fileService FileService;

    @PostMapping("/save")
    public ResponseEntity<fileEntity> saveFile(fileEntity file){

        fileEntity newFile = FileService.saveFile(file);
        return ResponseEntity.ok(newFile);
    }

    @GetMapping("/get")
    public ResponseEntity<fileEntity> getInformation(@RequestParam("creditId") long creditId,
                                                     @RequestParam("type") int type){
        fileEntity file = FileService.getInformation(creditId,type);
        return ResponseEntity.ok(file);
    }

    @PostMapping("/upload")
    public ResponseEntity<String> uploadFile(@RequestParam("file") MultipartFile file) {
        try {
            String fileUrl = FileService.uploadFile(file);
            return ok("File uploaded successfully: " + fileUrl);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("Error uploading file");
        }
    }

    @GetMapping("/download")
    public ResponseEntity<byte[]> downloadFile(@RequestParam String fileName) {
        try {
            byte[] fileData = FileService.downloadFile(fileName);

            // Configura los encabezados para la respuesta de la descarga
            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.APPLICATION_PDF);
            headers.setContentDisposition(ContentDisposition.builder("attachment")
                    .filename(fileName)
                    .build());

            return ok()
                    .headers(headers)
                    .body(fileData);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(null);
        }
    }
}
