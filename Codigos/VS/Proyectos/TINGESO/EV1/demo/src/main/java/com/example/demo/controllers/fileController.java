package com.example.demo.controllers;

import com.example.demo.entities.fileEntity;
import com.example.demo.repositories.fileRepository;
import com.example.demo.servicies.fileService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.Resource;
import org.springframework.core.io.UrlResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Optional;

@RestController
@RequestMapping("/api/file")
@CrossOrigin("*")
public class fileController {

    @Autowired
    fileService FileService;

    @Autowired
    fileRepository FileRepository;

    @PostMapping("/upload/{userId}")
    public ResponseEntity<String> uploadFile(@PathVariable long userId,
                                             @RequestParam int type,
                                             @RequestParam("file")MultipartFile file){
        try{
            String filePath = FileService.storeFile(file);

            fileEntity newFile = new fileEntity();
            newFile.setFileName(file.getOriginalFilename());
            newFile.setFilePath(filePath);
            newFile.setFileUserId(userId);
            newFile.setType(type);
            FileService.saveFile(newFile);

            return ResponseEntity.ok("Archivo subido con exito: " + filePath);
        } catch (IOException e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("Error al subir el archivo");
        }
    }

    @GetMapping("/download/{userId}")
    public ResponseEntity<Resource> downloadFile(@PathVariable long userId,
                                                 @RequestParam("type") int type){
        try{
            Optional<fileEntity> optionalFile = FileRepository.findByFileUserIdAndType(userId,type);

            if(optionalFile.isEmpty()){
                return ResponseEntity.notFound().build();
            }

            fileEntity file = optionalFile.get();
            Path filePath = Paths.get(file.getFilePath()).normalize();
            Resource resource = new UrlResource(filePath.toUri());

            if(!resource.exists()){
                return ResponseEntity.notFound().build();
            }

            return ResponseEntity.ok()
                    .contentType(MediaType.APPLICATION_PDF)
                    .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"" + resource.getFilename() + "\"")
                    .body(resource);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
}
