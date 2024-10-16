package com.example.demo.controllers;

import com.example.demo.entities.userEntity;
import com.example.demo.servicies.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.ArrayList;

@RestController
@RequestMapping("/api/user")
@CrossOrigin("*")
public class userController {

    @Autowired
    userService UserService;

    @GetMapping("/getUsers")
    public ResponseEntity<ArrayList<userEntity>> listUsers(){
        ArrayList<userEntity> users = UserService.getUsers();
        return ResponseEntity.ok(users);
    }

    @GetMapping("getUserById/{userId}")
    public ResponseEntity<userEntity> getUserById(@PathVariable Long userId) {
        userEntity user = UserService.getUserById(userId);
        return ResponseEntity.ok(user);
    }

    @GetMapping("getUserByRut/{userRut}")
    public ResponseEntity<userEntity> getUserByRut(@PathVariable String userRut){
        userEntity user = UserService.getUserByRut(userRut);
        return ResponseEntity.ok(user);
    }

    @GetMapping("getUserByEmail/{userEmail}")
    public ResponseEntity<userEntity> getUserByEmail(@PathVariable String userEmail){
        userEntity user = UserService.getUserByEmail(userEmail);
        return ResponseEntity.ok(user);
    }

    @PostMapping("/saveUser")
    public ResponseEntity<userEntity> saveUser(@RequestBody userEntity user) {
        userEntity newUser = UserService.saveUser(user);
        return ResponseEntity.ok(newUser);
    }

    @PostMapping("/login")
    public int login(@RequestBody userEntity user){
        return UserService.login(user.getUserEmail(),user.getUserPassword());
    }

    @PutMapping("/updateUser")
    public ResponseEntity<userEntity> updateUser(@RequestBody userEntity user){
        userEntity userUpdated = UserService.updateUser(user);
        return ResponseEntity.ok(userUpdated);
    }

    @DeleteMapping("deleteUserById/{userId}")
    public ResponseEntity<Boolean> deleteUserById(@PathVariable Long userId) throws Exception {
        var isDeleted = UserService.deleteUser(userId);
        return ResponseEntity.ok(isDeleted);
    }
}
