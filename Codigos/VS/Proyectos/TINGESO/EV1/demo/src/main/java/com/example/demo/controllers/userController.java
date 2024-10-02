package com.example.demo.controllers;

import com.example.demo.entities.userEntity;
import com.example.demo.services.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/api/v1/user")
@CrossOrigin("*")
public class userController {

    @Autowired
    userService UserService;

    @GetMapping("/")
    public ResponseEntity<List<userEntity>> listUsers(){

        List<userEntity> users = UserService.getUsers();
        return ResponseEntity.ok(users);
    }
}
