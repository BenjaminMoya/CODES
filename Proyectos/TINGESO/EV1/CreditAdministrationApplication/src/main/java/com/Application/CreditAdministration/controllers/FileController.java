package com.Application.CreditAdministration.controllers;

import com.Application.CreditAdministration.entities.FileEntity;
import com.Application.CreditAdministration.servicies.FileService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;

@RestController
@RequestMapping("/api/file")
@CrossOrigin("*")
public class FileController {

    @Autowired
    FileService fileService;

    @PostMapping("/upload/{id}/{type}")
    public int saveFile(@PathVariable long id,
                        @PathVariable int type,
                        @RequestParam("file") MultipartFile file) {
        try {
            return fileService.uploadFile(id, type, file);
        } catch (IOException e) {
            return 0;
        }
    }

    @GetMapping("/download/{id}/{type}")
    public ResponseEntity<byte[]> downloadFile(@PathVariable long id,
                                               @PathVariable int type) {
        FileEntity pdfFile = fileService.downloadFile(id,type);
        return ResponseEntity.ok()
                .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"" + pdfFile.getFilename() + "\"")
                .contentType(MediaType.APPLICATION_PDF)
                .body(pdfFile.getFileContent());
    }

    @DeleteMapping("/delete/{id}")
    public int deleteFiles(@PathVariable long id){
        try{
            fileService.deleteFiles(id);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }
}
