import json
import maya.cmds as cmds
import math

def matrix_to_quat(m):
    w = math.sqrt(1.0 + m[0] + m[5] + m[10]) / 2.0
    w4 = w * 4.0
    x = (m[6] - m[9]) / w4
    y = (m[8] - m[2]) / w4
    z = (m[1] - m[4]) / w4
    return [x, y, z, w]

jsonData = {}  
jsonData['GameObjects'] = []  

selected_obj = cmds.ls(sl=True, type='transform')
for curr_obj in selected_obj:
    translation = cmds.xform(curr_obj, query=True, translation=True, worldSpace=True)
    transformationMatrix = cmds.xform(curr_obj, query=True, matrix=True)
    orientation = matrix_to_quat(transformationMatrix)
    gameObjectName = ""
    gameObjectShader = "normalMapShader2"
    gameObjectColBoxSize = [ 1, 1, 1 ]
    gameObjectColSphereSize = 1
    gameObjectMass = 0.0;
    gameObjectColShape = "btBoxShape";
    if curr_obj.find("metal_ground_arena") >= 0:
        gameObjectName = "metal_ground_arena"
        gameObjectColBoxSize = [ 10, 0.2, 10 ]
    elif curr_obj.find("ground_arena") >= 0:
        gameObjectName = "ground_arena"
        gameObjectColBoxSize = [ 100, 0.2, 100 ]
    elif curr_obj.find("metal_fence_arena") >= 0:
        gameObjectName = "metal_fence_arena"
        gameObjectColBoxSize = [ 10, 2, 0.2 ]
    elif curr_obj.find("metal_goal_side_small") >= 0:
        gameObjectName = "metal_goal_side_small"
        gameObjectColBoxSize = [ 3.5, 2, 0.2 ]
    elif curr_obj.find("metal_goal_top") >= 0:
        gameObjectName = "metal_goal_top"
        gameObjectColBoxSize = [ 1, 0.1, 2 ]
    elif curr_obj.find("metal_goal_side") >= 0:
        gameObjectName = "metal_goal_side"
        gameObjectColBoxSize = [ 0.9, 2, 0.1 ]
    elif curr_obj.find("metal_goal_back") >= 0:
        gameObjectName = "metal_goal_back"
        translation[0] += 1
        gameObjectColBoxSize = [ 0.1, 2, 2 ]
    elif curr_obj.find("metal_pillar_arena") >= 0:
        gameObjectName = "metal_pillar_arena"
        gameObjectColBoxSize = [ 0.1, 0.1, 0.1 ]
    elif curr_obj.find("field_lights") >= 0:
        gameObjectName = "field_lights"
        gameObjectColBoxSize = [ 0.5, 0.5, 0.5 ]
    elif curr_obj.find("ball_arena") >= 0:
        gameObjectName = "ball_arena"
        gameObjectColSphereSize = 0.2
        gameObjectColBoxSize = [ 0.2, 0.2, 0.2 ]
        gameObjectMass = 1.0
        gameObjectColShape = "btSphereShape"
    
    if gameObjectName != "":
        jsonData['GameObjects'].append({
            'name': gameObjectName,
            'model': gameObjectName,
            'shader': gameObjectShader,
            'position': [translation[0], translation[1], translation[2]],
            "colliderposition": [translation[0], translation[1], translation[2]],
            'orientation': [orientation[0], orientation[1], orientation[2], orientation[3]],
            'scale': [1, 1, 1],
            'mass': [gameObjectMass],
            'collisionshape': gameObjectColShape,
            'spherecolsize': gameObjectColSphereSize,
            'collisionboxsize': gameObjectColBoxSize
        })

print jsonData

with open('H:\Year_3\Game engine\Buff Luigi\OpenGLVS\Level_Arena.json', 'w') as outfile:
    json.dump(jsonData, outfile, sort_keys=True, indent=2)