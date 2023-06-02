
/*

Role-Based Access Control (RBAC) is a widely used pattern for managing permissions and 
access control in systems. It provides a flexible and scalable approach to defining 
and enforcing access rights based on user roles.

In RBAC, access control is based on the roles that users have, rather than their 
individual identities. The key components of RBAC include roles, permissions, 
and user assignments. Let's explore each of these components in more detail:

1.  Roles: Roles represent sets of responsibilities or job functions within an 
    organization or system. Roles are defined based on the tasks and permissions 
    required to perform those functions. Examples of roles could be "Admin," "Manager,"
    or "User." Roles can be hierarchical, with sub-roles inheriting permissions from parent roles.

2.  Permissions: Permissions define the actions or operations that users can perform 
    within the system. Each role is associated with a set of permissions that determine 
    what actions are allowed or denied. Permissions can be granular, such as "create,"
    "read," "update," and "delete" for different resources or features.

3.  User Assignments: User assignments associate individual users with specific roles.
    Each user is assigned one or more roles that define their access rights. 
    By assigning roles to users, their permissions are automatically determined 
    based on the associated role(s).

The RBAC pattern provides several benefits, including:

- Simplified Administration: RBAC simplifies the management of user access by 
  grouping permissions into roles. Instead of managing access rights for individual
  users, administrators can assign and revoke roles, which automatically adjusts user permissions.

- Scalability: RBAC allows for easy scalability as new roles and permissions can
  be added without modifying the core access control logic. This flexibility 
  makes RBAC suitable for large and complex systems with evolving access requirements.

- Separation of Duties: RBAC supports the principle of separation of duties by 
  allowing the assignment of multiple roles to different users. This helps ensure
  that critical actions require the collaboration of multiple users, reducing the 
  risk of unauthorized activities.

- Enhanced Security: RBAC provides a structured and controlled approach to access 
  control, reducing the likelihood of human error and unauthorized access. 
  By strictly defining roles and permissions, RBAC helps enforce the principle 
  of least privilege, granting users only the permissions necessary for their roles.

To implement RBAC, you would typically design a system where user roles,
permissions, and user assignments are stored and managed. The system would 
include mechanisms to authenticate users, determine their assigned roles,
and enforce access control based on role-based permissions.

Overall, the RBAC pattern is a powerful approach to managing access control 
and enforcing security policies in systems, offering flexibility, scalability, and enhanced security.
*/
#include <iostream>
#include <unordered_map>
#include <vector>

// Define the Role class representing a user role
class Role {
public:
    Role(const std::string& name) : name_(name) {}

    const std::string& getName() const {
        return name_;
    }

private:
    std::string name_;
};

// Define the Permission class representing a specific action or operation
class Permission {
public:
    Permission(const std::string& name) : name_(name) {}

    const std::string& getName() const {
        return name_;
    }

private:
    std::string name_;
};

// Define the User class representing a system user
class User {
public:
    User(const std::string& username) : username_(username) {}

    const std::string& getUsername() const {
        return username_;
    }

private:
    std::string username_;
};

// Define the RBACManager class responsible for managing roles, permissions, and user assignments
class RBACManager {
public:
    void addRole(const Role& role) {
        roles_.emplace(role.getName(), role);
    }

    void addPermissionToRole(const Role& role, const Permission& permission) {
        rolePermissions_[role.getName()].push_back(permission);
    }

    void assignRoleToUser(const User& user, const Role& role) {
        userRoles_[user.getUsername()].push_back(role);
    }

    bool hasPermission(const User& user, const Permission& permission) {
        const auto& roles = userRoles_[user.getUsername()];
        for (const auto& role : roles) {
            const auto& permissions = rolePermissions_[role.getName()];
            for (const auto& perm : permissions) {
                if (perm.getName() == permission.getName()) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    std::unordered_map<std::string, Role> roles_;
    std::unordered_map<std::string, std::vector<Permission>> rolePermissions_;
    std::unordered_map<std::string, std::vector<Role>> userRoles_;
};

int main() {
    // Create RBAC manager
    RBACManager rbacManager;

    // Create roles
    Role adminRole("Admin");
    Role userRole("User");

    // Create permissions
    Permission createPermission("Create");
    Permission readPermission("Read");
    Permission updatePermission("Update");
    Permission deletePermission("Delete");

    // Add roles and permissions to the RBAC manager
    rbacManager.addRole(adminRole);
    rbacManager.addRole(userRole);

    rbacManager.addPermissionToRole(adminRole, createPermission);
    rbacManager.addPermissionToRole(adminRole, readPermission);
    rbacManager.addPermissionToRole(adminRole, updatePermission);
    rbacManager.addPermissionToRole(adminRole, deletePermission);

    rbacManager.addPermissionToRole(userRole, readPermission);
    rbacManager.addPermissionToRole(userRole, updatePermission);

    // Create users
    User user1("John");
    User user2("Alice");

    // Assign roles to users
    rbacManager.assignRoleToUser(user1, adminRole);
    rbacManager.assignRoleToUser(user2, userRole);

    // Check permissions for users
    Permission permissionToCheck("Read");
    std::cout << "User " << user1.getUsername() << " has permission to " << permissionToCheck.getName() << ": "
        << (rbacManager.hasPermission(user1, permissionToCheck) ? "Yes" : "No") << std::endl;

    permissionToCheck = Permission("Delete");
    
    return 0;
}