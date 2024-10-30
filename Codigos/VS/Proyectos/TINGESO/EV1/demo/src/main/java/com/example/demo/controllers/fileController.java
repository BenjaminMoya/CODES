package com.example.demo.controllers;

import com.example.demo.entities.fileEntity;
import com.example.demo.servicies.fileService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;

import static org.springframework.http.ResponseEntity.ok;

@RestController
@RequestMapping("/api/file")
@CrossOrigin("*")
public class fileController {

    @Autowired
    fileService FileService;

    @PostMapping("/upload/{id}/{type}")
    public int saveFile(@PathVariable long id,
                        @PathVariable int type,
                        @RequestParam("file") MultipartFile file) {
        try {
            return FileService.uploadFile(id, type, file);
        } catch (IOException e) {
            return 0;
        }
    }

    @GetMapping("/download/{id}/{type}")
    public ResponseEntity<byte[]> downloadFile(@PathVariable long id,
                                               @PathVariable int type) {
        fileEntity pdfFile = FileService.downloadFile(id,type);
        return ResponseEntity.ok()
                .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"" + pdfFile.getFilename() + "\"")
                .contentType(MediaType.APPLICATION_PDF)
                .body(pdfFile.getFileContent());
    }

    @DeleteMapping("/delete/{id}")
    public int deleteFiles(@PathVariable long id){
        try{
            FileService.deleteFiles(id);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }
}
